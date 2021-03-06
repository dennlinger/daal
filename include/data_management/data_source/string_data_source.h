/* file: string_data_source.h */
/*******************************************************************************
* Copyright 2014-2018 Intel Corporation.
*
* This software and the related documents are Intel copyrighted  materials,  and
* your use of  them is  governed by the  express license  under which  they were
* provided to you (License).  Unless the License provides otherwise, you may not
* use, modify, copy, publish, distribute,  disclose or transmit this software or
* the related documents without Intel's prior written permission.
*
* This software and the related documents  are provided as  is,  with no express
* or implied  warranties,  other  than those  that are  expressly stated  in the
* License.
*******************************************************************************/

/*
//++
//  Implementation of the string data source class.
//--
*/

#ifndef __STRING_DATA_SOURCE_H__
#define __STRING_DATA_SOURCE_H__

#include "services/daal_memory.h"
#include "data_management/data_source/data_source.h"
#include "data_management/data_source/csv_data_source.h"
#include "data_management/data/data_dictionary.h"
#include "data_management/data/numeric_table.h"
#include "data_management/data/homogen_numeric_table.h"

namespace daal
{
namespace data_management
{

namespace interface1
{
/**
 * @ingroup data_sources
 * @{
 */
/**
 *  <a name="DAAL-CLASS-DATA_MANAGEMENT__STRINGDATASOURCE"></a>
 *  \brief Specifies methods to access data stored in byte arrays in the C-string format
 *  \tparam _featureManager     FeatureManager used to get numeric data from file strings
 */
template< typename _featureManager, typename _summaryStatisticsType = DAAL_SUMMARY_STATISTICS_TYPE >
class StringDataSource : public CsvDataSource< _featureManager, _summaryStatisticsType >
{
public:
    using CsvDataSource<_featureManager,_summaryStatisticsType>::checkDictionary;
    using CsvDataSource<_featureManager,_summaryStatisticsType>::checkNumericTable;
    using CsvDataSource<_featureManager,_summaryStatisticsType>::freeNumericTable;
    using CsvDataSource<_featureManager,_summaryStatisticsType>::_dict;
    using CsvDataSource<_featureManager,_summaryStatisticsType>::_initialMaxRows;
    using CsvDataSource<_featureManager,_summaryStatisticsType>::loadDataBlock;

    using CsvDataSource<_featureManager,_summaryStatisticsType>::featureManager;

    using CsvDataSource<_featureManager,_summaryStatisticsType>::createDictionaryFromContext;

    /**
     *  Typedef that stores the parser datatype
     */
    typedef _featureManager FeatureManager;

protected:
    typedef data_management::HomogenNumericTable<DAAL_DATA_TYPE> DefaultNumericTableType;

    using CsvDataSource<_featureManager,_summaryStatisticsType>::_rawLineBuffer;
    using CsvDataSource<_featureManager,_summaryStatisticsType>::_rawLineBufferLen;
    using CsvDataSource<_featureManager,_summaryStatisticsType>::_rawLineLength;
    using CsvDataSource<_featureManager,_summaryStatisticsType>::enlargeBuffer;

public:
    /**
     *  Main constructor for a Data Source
     *  \param[in]  data                            Byte array in the C-string format
     *  \param[in]  doAllocateNumericTable          Flag that specifies whether a Numeric Table
     *                                              associated with a File Data Source is allocated inside the Data Source
     *  \param[in]  doCreateDictionaryFromContext   Flag that specifies whether a Data Dictionary
     *                                              is created from the context of the File Data Source
     *  \param[in]  initialMaxRows                  Initial value of maximum number of rows in Numeric Table allocated in loadDataBlock() method
     */
    StringDataSource( const byte *data,
                      DataSourceIface::NumericTableAllocationFlag doAllocateNumericTable    = DataSource::notAllocateNumericTable,
                      DataSourceIface::DictionaryCreationFlag doCreateDictionaryFromContext = DataSource::notDictionaryFromContext,
                      size_t initialMaxRows = 10):
    CsvDataSource<_featureManager,_summaryStatisticsType>(doAllocateNumericTable, doCreateDictionaryFromContext, initialMaxRows), _contextDictFlag(false)
    {
        setData( data );
    }

    ~StringDataSource() {}

    /**
     *  Sets a new string as a source for data
     *  \param[in]  data  Byte array in the C-string format
     */
    void setData( const byte *data )
    {
        if( !data )
        {
            this->_status.add(services::throwIfPossible(services::Status(services::ErrorNullPtr)));
            return;
        }
        _stringBufferPos = 0;
        _stringBuffer    = (char *)data;
    }

    /**
     *  Gets data source string data
     *  \return  Byte array in the C-string format
     */
    const byte *getData()
    {
        return (const byte *)(_stringBuffer);
    }

    /**
     *  Resets a data source string
     */
    void resetData()
    {
        _stringBufferPos = 0;
    }

public:
    services::Status createDictionaryFromContext() DAAL_C11_OVERRIDE
    {
        services::Status s = CsvDataSource<_featureManager,_summaryStatisticsType>::createDictionaryFromContext();
        _stringBufferPos = 0;
        return s;
    }

    DataSourceIface::DataSourceStatus getStatus() DAAL_C11_OVERRIDE
    {
        return (iseof() ? DataSourceIface::endOfData : DataSourceIface::readyForLoad);
    }

protected:
    bool iseof() const DAAL_C11_OVERRIDE
    {
        return (_stringBuffer[_stringBufferPos] == '\0');
    }

    int readLine(char *buffer, int count)
    {
        int pos = 0;
        for(;pos<count-1;pos++)
        {
            buffer[pos] = _stringBuffer[_stringBufferPos+pos];

            if( buffer[pos]=='\0' || buffer[pos]=='\n' )
            {
                break;
            }
        }
        if(buffer[pos]=='\n')
        {
            pos++;
        }
        _stringBufferPos += pos;
        buffer[pos] = '\0';
        return pos;
    }

    services::Status readLine() DAAL_C11_OVERRIDE
    {
        _rawLineLength = 0;
        while(!iseof())
        {
            const int readLen = readLine (_rawLineBuffer + _rawLineLength, (int)(_rawLineBufferLen - _rawLineLength));
            if (readLen <= 0)
            {
                _rawLineLength = 0;
                return services::Status();
            }
            _rawLineLength += readLen;
            if (_rawLineBuffer[_rawLineLength - 1] == '\n' || _rawLineBuffer[_rawLineLength - 1] == '\r')
            {
                while (_rawLineLength > 0 && (_rawLineBuffer[_rawLineLength - 1] == '\n' || _rawLineBuffer[_rawLineLength - 1] == '\r'))
                {
                    _rawLineLength--;
                }
                _rawLineBuffer[_rawLineLength] = '\0';
                return services::Status();
            }
            if(!enlargeBuffer())
                return services::Status(services::ErrorMemoryAllocationFailed);
        }
        return services::Status();
    }

private:
    char  *_stringBuffer;
    size_t _stringBufferPos;

    bool  _contextDictFlag;
};
/** @} */
} // namespace interface1
using interface1::StringDataSource;

}
}
#endif
