#include "wsjcpp_storages.h"
#include <algorithm>

// ***********************
// *** WSJCppStorageColumnDef
// ***********************

// ---------------------------------------------------------------------

WSJCppStorageColumnDef::WSJCppStorageColumnDef(const std::string &sColumnName) {
    TAG = "StorageColumnDef_" + sColumnName;
    // TODO validate column name

    m_sColumnName = sColumnName;
    m_bAutoIncrement = false;
    m_bNotNull = false;
    m_nTypeSize = 0;
    m_sType = "";
    m_bPrimaryKey = false;
    m_sDefaultValue = "";
    m_bEnableIndex = false;
    m_bEnableUniqueIndex = false;
    m_bDefaultValue = false;
}

// ---------------------------------------------------------------------

WSJCppStorageColumnDef &WSJCppStorageColumnDef::autoIncrement() {
    m_bAutoIncrement = true;
    return *this;
}

// ---------------------------------------------------------------------

WSJCppStorageColumnDef &WSJCppStorageColumnDef::notNull() {
    m_bNotNull = true;
    return *this;
}

// ---------------------------------------------------------------------

WSJCppStorageColumnDef &WSJCppStorageColumnDef::string(int nValue) {
    if (m_sType != "") {
        WSJCppLog::throw_err(TAG, "Datatype already defined: " + m_sType);
        return *this;
    }
    m_sType = "string";
    m_nTypeSize = nValue;
    return *this;
}

// ---------------------------------------------------------------------

WSJCppStorageColumnDef &WSJCppStorageColumnDef::text() {
    if (m_sType != "") {
        WSJCppLog::throw_err(TAG, "Datatype already defined: " + m_sType);
        return *this;
    }
    m_sType = "text";
    return *this;
}

// ---------------------------------------------------------------------

WSJCppStorageColumnDef &WSJCppStorageColumnDef::datetime() {
    if (m_sType != "") {
        WSJCppLog::throw_err(TAG, "Datatype already defined: " + m_sType);
        return *this;
    }
    m_sType = "datetime";
    return *this;
}

// ---------------------------------------------------------------------

WSJCppStorageColumnDef &WSJCppStorageColumnDef::number() {
    if (m_sType != "") {
        WSJCppLog::throw_err(TAG, "Datatype already defined: " + m_sType);
        return *this;
    }
    m_sType = "number";
    return *this;
}

// ---------------------------------------------------------------------

WSJCppStorageColumnDef &WSJCppStorageColumnDef::doubleNumber() {
    if (m_sType != "") {
        WSJCppLog::throw_err(TAG, "Datatype already defined: " + m_sType);
        return *this;
    }
    m_sType = "doubleNumber";
    return *this;
}


// ---------------------------------------------------------------------

WSJCppStorageColumnDef &WSJCppStorageColumnDef::primaryKey() {
    m_bPrimaryKey = true;
    return *this;
}

// ---------------------------------------------------------------------

WSJCppStorageColumnDef &WSJCppStorageColumnDef::defaultValue(const std::string& sDefaultValue) {
    m_sDefaultValue = sDefaultValue;
    m_bDefaultValue = true;
    return *this;
}

// ---------------------------------------------------------------------

WSJCppStorageColumnDef &WSJCppStorageColumnDef::enableIndex() {
    m_bEnableIndex = true;
    return *this;
}

// ---------------------------------------------------------------------

WSJCppStorageColumnDef &WSJCppStorageColumnDef::enableUniqueIndex(const std::string& sIndexName) {
    m_sNameOfUniqueIndex = sIndexName;
    m_bEnableUniqueIndex = true;
    return *this;
}

// ---------------------------------------------------------------------

std::string WSJCppStorageColumnDef::columnName() const {
    return m_sColumnName;
}

// ---------------------------------------------------------------------

std::string WSJCppStorageColumnDef::columnType() {
    return m_sType;
}

// ---------------------------------------------------------------------

std::string WSJCppStorageColumnDef::columnDefaultValue() {
    return m_sDefaultValue;
}

// ---------------------------------------------------------------------

bool WSJCppStorageColumnDef::isDefaultValue() {
    return m_bDefaultValue;
}

// ---------------------------------------------------------------------

int WSJCppStorageColumnDef::columnTypeSize() {
    return m_nTypeSize;
}

// ---------------------------------------------------------------------

bool WSJCppStorageColumnDef::isAutoIncrement() {
    return m_bAutoIncrement;
}

// ---------------------------------------------------------------------

bool WSJCppStorageColumnDef::isPrimaryKey() {
    return m_bPrimaryKey;
}

// ---------------------------------------------------------------------

bool WSJCppStorageColumnDef::isNotNull() {
    return m_bNotNull;
}

// ---------------------------------------------------------------------

bool WSJCppStorageColumnDef::isEnableIndex() {
    return m_bEnableIndex;
}

// ---------------------------------------------------------------------

bool WSJCppStorageColumnDef::isEnableUniqueIndex() {
    return m_bEnableUniqueIndex;
}

// ---------------------------------------------------------------------

std::string WSJCppStorageColumnDef::nameOfUniqueIndex() {
    return m_sNameOfUniqueIndex;
}

// ---------------------------------------------------------------------

// ***********************
// *** StorageChanges
// ***********************

// ---------------------------------------------------------------------

WSJCppStorageChanges::WSJCppStorageChanges(const std::string &sTableName) {
    TAG = "StorageChanges";
    m_sTableName = sTableName;
}

// ---------------------------------------------------------------------

std::string WSJCppStorageChanges::getTableName() const {
    return m_sTableName;
}

// ---------------------------------------------------------------------

WSJCppStorageChangesType WSJCppStorageChanges::getType() const {
    return WSJCppStorageChangesType::NOPE;
}

// ---------------------------------------------------------------------

std::string WSJCppStorageChanges::getStartApply() const {
    return "Appling changes for table " + m_sTableName;
}

// ---------------------------------------------------------------------

std::string WSJCppStorageChanges::getAppliedSuccess() const {
    return "Changes success applied for table " + m_sTableName;
}

// ---------------------------------------------------------------------

std::string WSJCppStorageChanges::getAppliedFailed() const {
    return "Could not apply changes for table " + m_sTableName;
}

// ---------------------------------------------------------------------

// ***********************
// *** StorageCreateTable
// ***********************

WSJCppStorageCreateTable::WSJCppStorageCreateTable(const std::string &sTableName) 
    : WSJCppStorageChanges(sTableName) {
    TAG = "WSJCppStorageCreateTable";
    // TODO validate table of name
}

// ---------------------------------------------------------------------

WSJCppStorageChangesType WSJCppStorageCreateTable::getType() const {
    return WSJCppStorageChangesType::CREATE_TABLE;
};

// ---------------------------------------------------------------------

std::string WSJCppStorageCreateTable::getStartApply() const {
    return "Creating table '" + m_sTableName + "'";
}

// ---------------------------------------------------------------------

std::string WSJCppStorageCreateTable::getAppliedSuccess() const {
    return "Created table '" +  m_sTableName + "'";
}

// ---------------------------------------------------------------------

std::string WSJCppStorageCreateTable::getAppliedFailed() const {
    return "Could not create table '" +  m_sTableName + "'";
}

// ---------------------------------------------------------------------

WSJCppStorageColumnDef &WSJCppStorageCreateTable::addColumn(const std::string &sColumnName) {
    for (int i = 0; i < m_vColumns.size(); i++) {
        if (m_vColumns[i].columnName() == sColumnName) {
            std::string sError = "Column '" + sColumnName + "' in table '" + m_sTableName + "' already exists";
            WSJCppLog::throw_err(TAG, sError);
        }
    }
    m_vColumns.push_back(WSJCppStorageColumnDef(sColumnName));
    return m_vColumns[m_vColumns.size()-1];
}

// ---------------------------------------------------------------------

const std::vector<WSJCppStorageColumnDef> &WSJCppStorageCreateTable::getColumns() const {
    return m_vColumns;
}

// ---------------------------------------------------------------------

// ***********************
// *** StorageModifyTable
// ***********************

WSJCppStorageModifyTable::WSJCppStorageModifyTable(const std::string &sTableName) 
    : WSJCppStorageChanges(sTableName) {
    TAG = "WSJCppStorageModifyTable";
    // TODO validate table of name
}

// ---------------------------------------------------------------------

WSJCppStorageChangesType WSJCppStorageModifyTable::getType() const {
    return WSJCppStorageChangesType::MODIFY_TABLE;
};

// ---------------------------------------------------------------------

std::string WSJCppStorageModifyTable::getStartApply() const {
    return "Modifing table " + m_sTableName;
}

// ---------------------------------------------------------------------

std::string WSJCppStorageModifyTable::getAppliedSuccess() const {
    return "Modified table " +  m_sTableName;
}

// ---------------------------------------------------------------------

std::string WSJCppStorageModifyTable::getAppliedFailed() const {
    return "Could not modify table " +  m_sTableName;
}

// ---------------------------------------------------------------------

WSJCppStorageColumnDef &WSJCppStorageModifyTable::addColumn(const std::string &sColumnName) {
    std::string sError;
    if (isColumnDefined(sColumnName, sError)) {
        WSJCppLog::throw_err(TAG, "addColumn, " + sError);
    }
    m_vAddColumns.push_back(WSJCppStorageColumnDef(sColumnName));
    return m_vAddColumns[m_vAddColumns.size()-1];
}

// ---------------------------------------------------------------------

WSJCppStorageColumnDef &WSJCppStorageModifyTable::alterColumn(const std::string &sColumnName) {
    std::string sError;
    if (isColumnDefined(sColumnName, sError)) {
        WSJCppLog::throw_err(TAG, "alterColumn, " + sError);
    }
    m_vAlterColumns.push_back(WSJCppStorageColumnDef(sColumnName));
    return m_vAlterColumns[m_vAlterColumns.size()-1];
}

// ---------------------------------------------------------------------

std::string WSJCppStorageModifyTable::dropColumn(const std::string &sColumnName) {
    std::string sError;
    if (isColumnDefined(sColumnName, sError)) {
        WSJCppLog::throw_err(TAG, "dropColumn, " + sError);
    }
    m_vDropColumns.push_back(sColumnName);
    return m_vDropColumns[m_vDropColumns.size()-1];
}

// ---------------------------------------------------------------------

const std::vector<WSJCppStorageColumnDef> &WSJCppStorageModifyTable::getAddColumns() const {
    return m_vAddColumns;
}

// ---------------------------------------------------------------------

const std::vector<WSJCppStorageColumnDef> &WSJCppStorageModifyTable::getAlterColumns() const {
    return m_vAlterColumns;
}

// ---------------------------------------------------------------------

const std::vector<std::string> &WSJCppStorageModifyTable::getDropColumns() const {
    return m_vDropColumns;
}

// ---------------------------------------------------------------------

bool WSJCppStorageModifyTable::isColumnDefined(const std::string &sColumnName, std::string &sError) const {
    for (int i = 0; i < m_vAddColumns.size(); i++) {
        if (m_vAddColumns[i].columnName() == sColumnName) {
            sError = "Column '" + sColumnName + "' in table '" + m_sTableName + "' already defined as 'add' ";
            return true;
        }
    }

    for (int i = 0; i < m_vAlterColumns.size(); i++) {
        if (m_vAlterColumns[i].columnName() == sColumnName) {
            sError = "Column '" + sColumnName + "' in table '" + m_sTableName + "' already defined as 'alter'";
            return true;
        }
    }

    for (int i = 0; i < m_vDropColumns.size(); i++) {
        if (m_vDropColumns[i] == sColumnName) {
            sError = "Column '" + sColumnName + "' in table '" + m_sTableName + "' already defined as 'drop'";
            return true;
        }
    }

    return false;
}

// ---------------------------------------------------------------------

// ***********************
// *** StorageDropTable
// ***********************

WSJCppStorageDropTable::WSJCppStorageDropTable(const std::string &sTableName) 
    : WSJCppStorageChanges(sTableName) {
    TAG = "WSJCppStorageDropTable";
    // TODO validate table of name
}

// ---------------------------------------------------------------------

WSJCppStorageChangesType WSJCppStorageDropTable::getType() const {
    return WSJCppStorageChangesType::DROP_TABLE;
};

// ---------------------------------------------------------------------

std::string WSJCppStorageDropTable::getStartApply() const {
    return "Dropping table " + m_sTableName;
}

// ---------------------------------------------------------------------

std::string WSJCppStorageDropTable::getAppliedSuccess() const {
    return "Dropped table " +  m_sTableName;
}

// ---------------------------------------------------------------------

std::string WSJCppStorageDropTable::getAppliedFailed() const {
    return "Could not drop table " +  m_sTableName;
}

// ---------------------------------------------------------------------

// ***********************
// *** StorageColumnValue
// ***********************

WSJCppStorageColumnValue::WSJCppStorageColumnValue(const std::string &sColumnName, WSJCppStorageColumnType nType) {
    m_sColumnName = sColumnName;
    m_nColumnType = nType;
}

// ---------------------------------------------------------------------

void WSJCppStorageColumnValue::setValue(std::string sValue) {
    m_sStringValue = sValue;
}

// ---------------------------------------------------------------------

void WSJCppStorageColumnValue::setValue(int nValue) {
    m_nIntValue = nValue;
}

// ---------------------------------------------------------------------

void WSJCppStorageColumnValue::setValue(double nValue) {
    m_nDoubleValue = nValue;
}

// ---------------------------------------------------------------------

std::string WSJCppStorageColumnValue::getColumnName() {
    return m_sColumnName;
}

// ---------------------------------------------------------------------

WSJCppStorageColumnType WSJCppStorageColumnValue::getColumnType() {
    return m_nColumnType;
}

// ---------------------------------------------------------------------

std::string WSJCppStorageColumnValue::getString() {
    return m_sStringValue;
}

// ---------------------------------------------------------------------

int WSJCppStorageColumnValue::getInt() {
    return m_nIntValue;
}

// ---------------------------------------------------------------------

double WSJCppStorageColumnValue::getDouble() {
    return m_nDoubleValue;
}

// ---------------------------------------------------------------------

// ***********************
// *** WSJCppStorageInsert
// ***********************

WSJCppStorageInsert::WSJCppStorageInsert(const std::string &sTableName)
    : WSJCppStorageChanges(sTableName) {
    TAG = "WSJCppStorageInsert";
    m_sTableName = sTableName;
}

// ---------------------------------------------------------------------

WSJCppStorageChangesType WSJCppStorageInsert::getType() const {
    return WSJCppStorageChangesType::INSERT_ROW;
};

// ---------------------------------------------------------------------

std::string WSJCppStorageInsert::getStartApply() const {
    return "Inserting into table " + m_sTableName;
}

// ---------------------------------------------------------------------

std::string WSJCppStorageInsert::getAppliedSuccess() const {
    return "Inserted into table " +  m_sTableName;
}

// ---------------------------------------------------------------------

std::string WSJCppStorageInsert::getAppliedFailed() const {
    return "Could not insert into table " +  m_sTableName;
}

// ---------------------------------------------------------------------

void WSJCppStorageInsert::bindValue(const std::string &sColumnName, const std::string &sValue) {
    if (this->exists(sColumnName)) {
        WSJCppLog::throw_err(TAG, "Skip. Already defined " + m_sTableName + "." + sColumnName);
        return;
    }
    WSJCppStorageColumnValue val(sColumnName, WSJCppStorageColumnType::STRING);
    val.setValue(sValue);
    m_vValues.push_back(val);
}

// ---------------------------------------------------------------------

void WSJCppStorageInsert::bindValue(const std::string &sColumnName, int nValue) {
    if (this->exists(sColumnName)) {
        WSJCppLog::throw_err(TAG, "Skip. Already defined " + m_sTableName + "." + sColumnName);
        return;
    }
    WSJCppStorageColumnValue val(sColumnName, WSJCppStorageColumnType::NUMBER);
    val.setValue(nValue);
    m_vValues.push_back(val);
}

// ---------------------------------------------------------------------

void WSJCppStorageInsert::bindValue(const std::string &sColumnName, double nValue) {
    if (this->exists(sColumnName)) {
        WSJCppLog::throw_err(TAG, "Skip. Already defined " + m_sTableName + "." + sColumnName);
        return;
    }
    WSJCppStorageColumnValue val(sColumnName, WSJCppStorageColumnType::DOUBLE_NUMBER);
    val.setValue(nValue);
    m_vValues.push_back(val);
}

// ---------------------------------------------------------------------

std::vector<WSJCppStorageColumnValue> WSJCppStorageInsert::values() const {
    return m_vValues;
}

// ---------------------------------------------------------------------

bool WSJCppStorageInsert::exists(const std::string &sColumnName) {
    for (int i = 0; i < m_vValues.size(); i++) {
        if (m_vValues[i].getColumnName() == sColumnName) {
            return true;
        }
    }
    return false;
}

// ---------------------------------------------------------------------

bool WSJCppStorageInsert::isValid(const WSJCppStorageTable &storageTable) const {
    if (storageTable.getTableName() != m_sTableName) {
        WSJCppLog::err(TAG, "Expeceted '" + m_sTableName + "', but got '" + storageTable.getTableName() + "'");
        return false;
    }

    std::vector<WSJCppStorageColumnDef> vColumns = storageTable.getColumns();
    std::vector<std::string> vCurrentColumns;
    
    for (int x = 0; x < m_vValues.size(); x++) {
        bool bFound = false;
        WSJCppStorageColumnValue val = m_vValues[x];
        vCurrentColumns.push_back(val.getColumnName());
        for (int y = 0; y < vColumns.size(); y++) {
            WSJCppStorageColumnDef st = vColumns[y];
            if (st.columnName() == val.getColumnName()) {
                if (val.getColumnType() == WSJCppStorageColumnType::STRING
                    && (st.columnType() == "string" || st.columnType() == "datetime" || st.columnType() == "text")) {
                    bFound = true;
                    break;
                } else if (val.getColumnType() == WSJCppStorageColumnType::NUMBER && st.columnType() == "number") {
                    bFound = true;
                    break;
                } else if (val.getColumnType() == WSJCppStorageColumnType::DOUBLE_NUMBER && st.columnType() == "doubleNumber") {
                    bFound = true;
                    break;
                } else {
                    WSJCppLog::err(TAG, "StorageInsert::isValid. In struct '" + m_sTableName + "' column '" + val.getColumnName() + "'."
                        " Expected datatype '" + st.columnType() + "', but got '" + std::to_string(val.getColumnType()) + "'");
                    return false;
                }
            }
        }
        if (!bFound) {
            WSJCppLog::err(TAG, "StorageInsert::isValid. Struct '" + m_sTableName + "' has not column '" + val.getColumnName() + "'");
            return false;
        }
    }

    for (int i = 0; i < vColumns.size(); i++) {
        if (!vColumns[i].isAutoIncrement() && vColumns[i].isNotNull()) {
            if (std::find(vCurrentColumns.begin(), vCurrentColumns.end(), vColumns[i].columnName()) == vCurrentColumns.end()) {
                WSJCppLog::err(TAG, "Missing require field '" + m_sTableName + "." + vColumns[i].columnName() + "'");
                return false;
            }
        }
    }
    return true;
}

// ---------------------------------------------------------------------

// ***********************
// *** StorageUpdate
// ***********************

// ---------------------------------------------------------------------

/*
WSJCppStorageUpdate::WSJCppStorageUpdate(const StorageStruct &storageStruct) {
    m_storageStruct = storageStruct;
}
// ---------------------------------------------------------------------
void WSJCppStorageUpdate::bindValue(const std::string &sColumnName, const std::string &sValue) {
}
// ---------------------------------------------------------------------
void WSJCppStorageUpdate::bindValue(const std::string &sColumnName, int nValue) {
}
// ---------------------------------------------------------------------
void WSJCppStorageUpdate::bindValue(const std::string &sColumnName, double nValue) {
}
// ---------------------------------------------------------------------
std::vector<WSJCppStorageColumnValue> StorageUpdate::values() const {
}
// ---------------------------------------------------------------------
bool WSJCppStorageUpdate::isValid() const {
    return false;
}
// ---------------------------------------------------------------------
*/

// ---------------------------------------------------------------------

WSJCppStorageTable::WSJCppStorageTable(const std::string &sTableName) {
    m_sTableName = sTableName;
    TAG = "WSJCppStorageTable";
}

// ---------------------------------------------------------------------

WSJCppStorageTable::WSJCppStorageTable(WSJCppStorageCreateTable &createTable) {
    m_sTableName = createTable.getTableName();
    const std::vector<WSJCppStorageColumnDef> &list = createTable.getColumns();
    for (int i = 0; i < list.size(); i++) {
        m_vColumns.push_back(list[i]);
    }
}

// ---------------------------------------------------------------------

std::string WSJCppStorageTable::getTableName() const {
    return m_sTableName;
}

// ---------------------------------------------------------------------

const std::vector<WSJCppStorageColumnDef> &WSJCppStorageTable::getColumns() const {
    return m_vColumns;
}

// ---------------------------------------------------------------------

void WSJCppStorageTable::mergeWith(WSJCppStorageModifyTable &modifyTable) {

    // TODO check indexes
    std::vector<std::string> vDropColumns = modifyTable.getDropColumns();
    for (int i = 0; i < vDropColumns.size(); i++) {
        bool bFound = false;
        std::string sColumnName = vDropColumns[i];
        for (int i = 0; i < m_vColumns.size(); i++) {
            if (m_vColumns[i].columnName() == sColumnName) {
                m_vColumns.erase(m_vColumns.begin() + i);
                bFound = true;
                break;
            }
        }
        if (!bFound) {
            WSJCppLog::throw_err(TAG, "Not found column " + sColumnName + " in table " + m_sTableName);
        }
    }

    std::vector<WSJCppStorageColumnDef> vAddColumns = modifyTable.getAddColumns();
    for (int i = 0; i < vAddColumns.size(); i++) {
        bool bFound = false;
        WSJCppStorageColumnDef c = vAddColumns[i];
        for (int i = 0; i < m_vColumns.size(); i++) {
            if (m_vColumns[i].columnName() == c.columnName()) {
                bFound = true;
            }
        }
        if (bFound) {
            WSJCppLog::throw_err(TAG, "Column already defined " + c.columnName() + " in table " + m_sTableName);
        } else {
            m_vColumns.push_back(c);
        }
    }

    // TODO check indexes
    std::vector<WSJCppStorageColumnDef> vAlterColumns = modifyTable.getAlterColumns();
    for (int i = 0; i < vAlterColumns.size(); i++) {
        bool bFound = false;
        WSJCppStorageColumnDef c = vAlterColumns[i];
        for (int i = 0; i < m_vColumns.size(); i++) {
            if (m_vColumns[i].columnName() == c.columnName()) {
                if (m_vColumns[i].isEnableIndex()) {
                    c.enableIndex();
                }
                m_vColumns[i] = c;
                bFound = true;
            }
        }
        if (!bFound) {
            WSJCppLog::throw_err(TAG, "Problem with alter column '" + c.columnName() + "'. It's not defined in table '" + m_sTableName + "'");
        }
    }
}

// ---------------------------------------------------------------------

// ***********************
// *** StorageConnection
// ***********************

WSJCppStorageConnection::WSJCppStorageConnection() {
    m_nCreated = WSJCppCore::currentTime_milliseconds();
    TAG = "WSJCppStorageConnection";
}

WSJCppStorageConnection::~WSJCppStorageConnection() {
    // Nothing
}

// ---------------------------------------------------------------------

long WSJCppStorageConnection::created() { // TODO 
    return m_nCreated;
}

// ---------------------------------------------------------------------

long WSJCppStorageConnection::getConnectionDurationInSeconds() {
    long nRet = WSJCppCore::currentTime_milliseconds() - m_nCreated;
    nRet = nRet / 1000;
    return nRet;
}

// ---------------------------------------------------------------------

// ***********************
// *** Storage
// ***********************

WSJCppStorage::WSJCppStorage() {
    TAG = "WSJCppStorage";
}

// ---------------------------------------------------------------------

bool WSJCppStorage::addStorageChanges(WSJCppStorageChanges &storageChanges) {
    std::string sTableName = storageChanges.getTableName();
    std::map<std::string, WSJCppStorageTable>::iterator it = m_mapTables.find(sTableName);

    if (storageChanges.getType() == WSJCppStorageChangesType::CREATE_TABLE) {
        if (it != m_mapTables.end()) {
            WSJCppLog::err(TAG, "Table '" + sTableName + "' already defined");
            WSJCppLog::warn(TAG, "TODO need drop table");
            return false;
        }
        WSJCppStorageTable tbl((WSJCppStorageCreateTable &)storageChanges);
        m_mapTables.insert(std::pair<std::string,WSJCppStorageTable>(sTableName,tbl) );
    } else if (storageChanges.getType() == WSJCppStorageChangesType::DROP_TABLE) {
        if (it == m_mapTables.end()) {
            WSJCppLog::throw_err(TAG, "Not found table '" + sTableName + "'");
        }
        m_mapTables.erase(sTableName);
    } else if (storageChanges.getType() == WSJCppStorageChangesType::MODIFY_TABLE) {
        if (it == m_mapTables.end()) {
            WSJCppLog::throw_err(TAG, "Not found table '" + sTableName + "'");
        }
        it->second.mergeWith((WSJCppStorageModifyTable &)storageChanges);
    } else if (storageChanges.getType() == WSJCppStorageChangesType::INSERT_ROW) {
        // skip
    } else {
        WSJCppLog::throw_err(TAG, "addStorageChanges, Unknown operation with table");
    }
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppStorage::executeStorageChanges(WSJCppStorageConnection *pConn, WSJCppStorageChanges &storageChanges) {
    std::string sTableName = storageChanges.getTableName();
    std::vector<std::string> vQueries;

    if (storageChanges.getType() == WSJCppStorageChangesType::CREATE_TABLE) {
        WSJCppStorageCreateTable createTable = (WSJCppStorageCreateTable &)storageChanges;
        vQueries = this->prepareSqlQueries(createTable);
    } else if (storageChanges.getType() == WSJCppStorageChangesType::MODIFY_TABLE) {
        WSJCppStorageModifyTable modifyTable = (WSJCppStorageModifyTable &)storageChanges;
        vQueries = this->prepareSqlQueries(modifyTable);
    } else if (storageChanges.getType() == WSJCppStorageChangesType::DROP_TABLE) {
        WSJCppStorageDropTable dropTable = (WSJCppStorageDropTable &)storageChanges;
        vQueries = this->prepareSqlQueries(dropTable);
    } else if (storageChanges.getType() == WSJCppStorageChangesType::INSERT_ROW) {
        WSJCppStorageInsert insRow = (WSJCppStorageInsert &)storageChanges;
        WSJCppStorageTable tableDef = getTableDef(insRow.getTableName());
        if (!insRow.isValid(tableDef)) {
            WSJCppLog::throw_err(TAG, "Insert into table '" + insRow.getTableName() + "' is invalid");
        }
        vQueries = this->prepareSqlQueries(insRow);
    } else {
        throw std::runtime_error("Could not support type of StorageChanges");
    }

    WSJCppLog::info(TAG, storageChanges.getStartApply());
    for (int i = 0; i < vQueries.size(); i++) {
        std::string sQuery = vQueries[i];
        if (!pConn->executeQuery(sQuery)) {
            WSJCppLog::throw_err(TAG, storageChanges.getAppliedFailed() + "\n    query -> " + sQuery);
            return false;
        }
    }

    if (!this->addStorageChanges(storageChanges)) {
        WSJCppLog::throw_err(TAG, storageChanges.getAppliedFailed());
        return false;
    }
    WSJCppLog::ok(TAG, storageChanges.getAppliedSuccess());
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppStorage::insertRow(WSJCppStorageConnection *pConn, const WSJCppStorageInsert &storageInsert) {

    std::string sTableName = storageInsert.getTableName();
    WSJCppStorageTable tableDef = getTableDef(sTableName);

    if (!storageInsert.isValid(tableDef)) {
        return false;
    }

    std::vector<std::string> v = this->prepareSqlQueries(storageInsert);
    for (int i = 0; i < v.size(); i++) {
        std::string sQuery = v[i];
        if (!pConn->executeQuery(sQuery)) {
            return false;
        }
    }
    return true;
}

// ---------------------------------------------------------------------

const std::map<std::string, WSJCppStorageTable> &WSJCppStorage::getTables() {
    return m_mapTables;
}

// ---------------------------------------------------------------------

bool WSJCppStorage::existsTable(const std::string &sTableName) {
    std::map<std::string, WSJCppStorageTable>::iterator it = m_mapTables.find(sTableName);
    return (it != m_mapTables.end());
}

// ---------------------------------------------------------------------

const WSJCppStorageTable &WSJCppStorage::getTableDef(const std::string &sTableName) {
    std::map<std::string, WSJCppStorageTable>::iterator it = m_mapTables.find(sTableName);
    if (it == m_mapTables.end()) {
        WSJCppLog::throw_err(TAG, "Table " + sTableName + " does not exists");
    }
    return it->second; 
}

// ---------------------------------------------------------------------

std::map<std::string, IFabricWSJCppStorage*> *g_pFabricWSJCppStorages = NULL;

// ---------------------------------------------------------------------

void WSJCppStorages::initGlobalVariables() {
    if (g_pFabricWSJCppStorages == NULL) {
        // WSJCppLog::info(std::string(), "Create employees map");
        g_pFabricWSJCppStorages = new std::map<std::string, IFabricWSJCppStorage*>();
    }
}

// ---------------------------------------------------------------------

void WSJCppStorages::add(const std::string &sType, IFabricWSJCppStorage* pStorage) {
    WSJCppStorages::initGlobalVariables();
    const std::string TAG = "addStorage";
    if (g_pFabricWSJCppStorages->count(sType) > 0) {
        WSJCppLog::err(TAG, sType + " - storage already registered");
    } else {
        g_pFabricWSJCppStorages->insert(std::pair<std::string, IFabricWSJCppStorage*>(sType,pStorage));
        // WSJCppLog::info(sType, "Registered");
    }
}

// ---------------------------------------------------------------------

std::vector<std::string> WSJCppStorages::list() {
    WSJCppStorages::initGlobalVariables();
    std::vector<std::string> vResult;
    std::map<std::string, IFabricWSJCppStorage*>::iterator it;
    for (it = g_pFabricWSJCppStorages->begin(); it != g_pFabricWSJCppStorages->end(); it++) {
        vResult.push_back(it->first);
    }
    return vResult;
}

// ---------------------------------------------------------------------

bool WSJCppStorages::support(const std::string &sType) {
    WSJCppStorages::initGlobalVariables();
    return g_pFabricWSJCppStorages->count(sType) != 0;
}

// ---------------------------------------------------------------------

WSJCppStorage* WSJCppStorages::create(const std::string &sType) {
    WSJCppStorages::initGlobalVariables();
    std::string TAG = "create";
    IFabricWSJCppStorage *pFabricWSJCppStorage = nullptr;
    if (g_pFabricWSJCppStorages->count(sType)) {
        pFabricWSJCppStorage = g_pFabricWSJCppStorages->at(sType);
        return pFabricWSJCppStorage->create();
    }
    WSJCppLog::throw_err(TAG, "Not found storage by name '" + sType + "'");
    return nullptr;
}

// ---------------------------------------------------------------------
// class StorageUpdateBase

WSJCppStorageUpdateBase::WSJCppStorageUpdateBase(const std::string &sFromVersion, const std::string &sVersion, const std::string &sDescription) {
    TAG = "Update_" + sVersion;
    m_sFromVersion = sFromVersion;
    m_sVersion = sVersion;
    m_sDescription = sDescription;
    
    if (sFromVersion != "") {
        WSJCppStorageUpdateBase *pUpdate = WSJCppStorageUpdates::findUpdateVersion(sFromVersion);
        if (pUpdate == nullptr) {
            WSJCppLog::throw_err(TAG, "Not found storage update version: '" + sFromVersion + "'");
        }
    }

    {
        WSJCppStorageUpdateBase *pUpdate = WSJCppStorageUpdates::findUpdateVersion(sVersion);
        if (pUpdate != nullptr) {
            WSJCppLog::throw_err(TAG, "Storage updates already has update with this version: '" + sVersion + "'");
        }
    }
    
    WSJCppStorageUpdates::initGlobalVariables();
    g_pWSJCppStorageUpdates->push_back(this);
}

// ---------------------------------------------------------------------

const std::string &WSJCppStorageUpdateBase::from_version() {
    return m_sFromVersion;
}

// ---------------------------------------------------------------------

const std::string &WSJCppStorageUpdateBase::version() {
    return m_sVersion;
}

// ---------------------------------------------------------------------

const std::string &WSJCppStorageUpdateBase::description() {
    return m_sDescription;
}

// ---------------------------------------------------------------------

const std::vector<WSJCppStorageChanges *> &WSJCppStorageUpdateBase::getChanges() {
    return m_vStorageChanges;
}

// ---------------------------------------------------------------------

void WSJCppStorageUpdateBase::setWeight(int nWeight) {
    m_nWeight = nWeight;
}

// ---------------------------------------------------------------------

int WSJCppStorageUpdateBase::getWeight() {
    return m_nWeight;
}

// ---------------------------------------------------------------------

WSJCppStorageCreateTable *WSJCppStorageUpdateBase::createTable(std::string sTableName) {
    checkTableName(sTableName);
    WSJCppStorageCreateTable *pCreateTable = new WSJCppStorageCreateTable(sTableName);
    m_vStorageChanges.push_back(pCreateTable);
    return pCreateTable;
}

// ---------------------------------------------------------------------

WSJCppStorageModifyTable *WSJCppStorageUpdateBase::modifyTable(std::string sTableName) {
    checkTableName(sTableName);
    WSJCppStorageModifyTable *pModifyTable = new WSJCppStorageModifyTable(sTableName);
    m_vStorageChanges.push_back(pModifyTable);
    return pModifyTable;
}

// ---------------------------------------------------------------------

WSJCppStorageDropTable *WSJCppStorageUpdateBase::dropTable(std::string sTableName) {
    checkTableName(sTableName);
    WSJCppStorageDropTable *pDropTable = new WSJCppStorageDropTable(sTableName);
    m_vStorageChanges.push_back(pDropTable);
    return pDropTable;
}

WSJCppStorageInsert *WSJCppStorageUpdateBase::insertIntoTable(std::string sTableName) {
    WSJCppStorageInsert *pInsert = new WSJCppStorageInsert(sTableName);
    m_vStorageChanges.push_back(pInsert);
    return pInsert;
}

// ---------------------------------------------------------------------

void WSJCppStorageUpdateBase::checkTableName(std::string sTableName) {
    // TODO check table name + runtime error
}

// ---------------------------------------------------------------------
// StorageUpdates

std::vector<WSJCppStorageUpdateBase *> *g_pWSJCppStorageUpdates = nullptr;

// ---------------------------------------------------------------------

void WSJCppStorageUpdates::initGlobalVariables() {
    if (g_pWSJCppStorageUpdates == NULL) {
        // WSJCppLog::info(std::string(), "Create list updates");
        g_pWSJCppStorageUpdates = new std::vector<WSJCppStorageUpdateBase *>();
    }
}

// ---------------------------------------------------------------------

int WSJCppStorageUpdates::calculateWeight(int nWeight, const std::string &sVersion) {
    int nRet = nWeight;
    WSJCppStorageUpdateBase *pCurrentUpdate = WSJCppStorageUpdates::findUpdateVersion(sVersion);
    if (pCurrentUpdate == nullptr) {
        return nRet;
    }
    nRet++;
    std::vector<WSJCppStorageUpdateBase *> vChildUpdates;
    for (int i = 0; i < g_pWSJCppStorageUpdates->size(); i++) {
        WSJCppStorageUpdateBase *pUpdate = g_pWSJCppStorageUpdates->at(i);
        if (sVersion == pUpdate->from_version()) {
            nRet = calculateWeight(nRet, pUpdate->version());
        }
    }
    return nRet;
}

// ---------------------------------------------------------------------

void WSJCppStorageUpdates::sortByWeight(std::vector<WSJCppStorageUpdateBase*> &vUpdates) {
    if (vUpdates.size() <= 1) {
        return;
    }
    for (int i = 0; i < vUpdates.size(); i++) {
        int nWeight = calculateWeight(0, vUpdates[i]->version());
        vUpdates[i]->setWeight(nWeight);
    }

    bool bSorted = false;
    while (!bSorted) {
        bSorted = true;
        for (int i = 0; i < vUpdates.size()-1; i++) {
            if (vUpdates[i]->getWeight() > vUpdates[i+1]->getWeight()) {
                WSJCppStorageUpdateBase *p = vUpdates[i];
                vUpdates[i] = vUpdates[i+1];
                vUpdates[i+1] = p;
                bSorted = false;
            }
        }
    }
}

// ---------------------------------------------------------------------

std::vector<WSJCppStorageUpdateBase *> WSJCppStorageUpdates::findUpdatesFromVersion(const std::string &sFromVersion) {
    std::vector<WSJCppStorageUpdateBase *> vFoundUpdates;
    for (int i = 0; i < g_pWSJCppStorageUpdates->size(); i++) {
        WSJCppStorageUpdateBase * pUpdate = g_pWSJCppStorageUpdates->at(i);
        if (pUpdate->from_version() == sFromVersion) {
            vFoundUpdates.push_back(pUpdate);
        }
    }
    return vFoundUpdates;
}

// ---------------------------------------------------------------------

void WSJCppStorageUpdates::pushUpdatesFromVersion(std::vector<WSJCppStorageUpdateBase *> &vSortedUpdates, const std::string &sFromVersion) {
    std::vector<WSJCppStorageUpdateBase *> vFoundUpdates = findUpdatesFromVersion(sFromVersion);
    sortByWeight(vFoundUpdates);
    // std::cout << std::to_string(vFoundUpdates.size()) << std::endl;
    if (vFoundUpdates.size() == 0) {
        return;
    }

    for (int i = 0; i < vFoundUpdates.size(); i++) {
        vSortedUpdates.push_back(vFoundUpdates[i]);
        pushUpdatesFromVersion(vSortedUpdates, vFoundUpdates[i]->version());
    }
}

// ---------------------------------------------------------------------

std::vector<WSJCppStorageUpdateBase *> WSJCppStorageUpdates::getSortedStorageUpdates() {
    WSJCppStorageUpdates::initGlobalVariables();
    // calculate weights
    std::vector<WSJCppStorageUpdateBase *> vSortedUpdates;
    pushUpdatesFromVersion(vSortedUpdates, "");
    return vSortedUpdates;
}

// ---------------------------------------------------------------------

WSJCppStorageUpdateBase* WSJCppStorageUpdates::findUpdateFromVersion(const std::string &sFromVersion) {
    WSJCppStorageUpdates::initGlobalVariables();
    std::string TAG = "StorageUpdates::findUpdateFromVersion";
    WSJCppStorageUpdateBase* pRet = nullptr;
    for (int i = 0; i < g_pWSJCppStorageUpdates->size(); i++) {
        WSJCppStorageUpdateBase* pUpdate = g_pWSJCppStorageUpdates->at(i);
        if (sFromVersion == pUpdate->from_version()) {
            if (pRet == nullptr) {
                pRet = pUpdate;
            } else {
                WSJCppLog::throw_err(TAG, "Already defined update with from_version " + sFromVersion);
            }
        }
    }
    return pRet;
}

// ---------------------------------------------------------------------

WSJCppStorageUpdateBase* WSJCppStorageUpdates::findUpdateVersion(const std::string &sVersion) {
    WSJCppStorageUpdates::initGlobalVariables();
    std::string TAG = "WSJCppStorageUpdates::findUpdateVersion";
    WSJCppStorageUpdateBase* pRet = nullptr;
    for (int i = 0; i < g_pWSJCppStorageUpdates->size(); i++) {
        WSJCppStorageUpdateBase* pUpdate = g_pWSJCppStorageUpdates->at(i);
        if (sVersion == pUpdate->version()) {
            if (pRet == nullptr) {
                pRet = pUpdate;
            } else {
                WSJCppLog::throw_err(TAG, "Already defined update with version " + sVersion);
            }
        }
    }
    return pRet;
}

// ---------------------------------------------------------------------
/*
bool StorageUpdates::apply(Storage *pStorage) {
    StorageUpdates::initGlobalVariables();
    std::string TAG = "StorageUpdates::apply";
    StorageConnection *pConn = pStorage->connect();
    if (pConn == nullptr) {
        WSJCppLog::err(TAG, "Could not connect to database");
        return false;
    } else {
        WSJCppLog::ok(TAG, "Successfully connection to database");
    }
    std::string sFirstVersion = "";
    std::string sLastVersion = pConn->lastDatabaseVersion();
    WSJCppLog::info(TAG, "Last Version -> '" + sLastVersion + "'");
    // restore struct of storage before sLastVersion
    bool bHasUpdates = true;
    while (bHasUpdates) {
        bHasUpdates = false;
        StorageUpdateBase* pUpdate = StorageUpdates::findUpdateFromVersion(sFirstVersion);
        if (pUpdate != nullptr) {
            if (sFirstVersion != sLastVersion) {
                sFirstVersion = pUpdate->version();
                bHasUpdates = true;
                std::string error = "";
                WSJCppLog::info(TAG, "Apply changes '" + pUpdate->from_version() + "' -> '" + pUpdate->version() + "'");
                // Apply changes
                std::vector<StorageChanges *> vStorageChanges = pUpdate->getChanges();
                for (int i = 0; i < vStorageChanges.size(); i++) {
                    StorageChanges *pChanges = vStorageChanges[i];
                    if (pChanges->getType() == WSJCppStorageChangesType::NOPE) {
                        std::string sError = "Not allowed use a WSJCppStorageChangesType::NOPE";
                        WSJCppLog::throw_err(TAG, sError);
                    }
                    if (!pStorage->addStorageChanges(*pChanges)) {
                        error = "Problem add storage changes '" + pChanges->getTableName() + "' in version " + pUpdate->version();
                        delete pConn;
                        return false;
                    }
                }
            }
        }
    }
    // apply new updates
    WSJCppLog::info(TAG, "apply new updates");
    bHasUpdates = true;
    while (bHasUpdates) {
        bHasUpdates = false;
        StorageUpdateBase* pUpdate = StorageUpdates::findUpdateFromVersion(sLastVersion);
        if (pUpdate != nullptr) {
            WSJCppLog::info(TAG, "Installing update '" + pUpdate->from_version() + "' -> '" + pUpdate->version() + "': " + pUpdate->description());
            sLastVersion = pUpdate->version();
            bHasUpdates = true;
            std::string error = "";
            // Apply changes
            std::vector<StorageChanges *> vStorageChanges = pUpdate->getChanges();
            for (int i = 0; i < vStorageChanges.size(); i++) {
                StorageChanges *pChanges = vStorageChanges[i];
                if (pChanges->getType() == WSJCppStorageChangesType::NOPE) {
                    std::string sError = "Not allowed use a WSJCppStorageChangesType::NOPE";
                    WSJCppLog::err(TAG, sError);
                    throw std::runtime_error(sError);
                }
                if (!pStorage->executeStorageChanges(pConn, *pChanges)) {
                    error = "Problem with table '" + pChanges->getTableName() + "' in version " + pUpdate->version();
                    delete pConn;
                    return false;
                }
            }
            pConn->insertUpdateInfo(pUpdate->version(), pUpdate->description());
        }
    }
    return true;
}
*/
// ---------------------------------------------------------------------

void WSJCppStorageUpdates::applyAllStorageChanges(WSJCppStorage *pStorage, WSJCppStorageUpdateBase *pUpdate) {
    std::string TAG = "StorageUpdates::applyAllStorageChanges";
    WSJCppLog::info(TAG, "Apply changes '" + pUpdate->from_version() + "' -> '" + pUpdate->version() + "'");

    // Apply changes
    std::vector<WSJCppStorageChanges *> vStorageChanges = pUpdate->getChanges();
    for (int i = 0; i < vStorageChanges.size(); i++) {
        WSJCppStorageChanges *pChanges = vStorageChanges[i];
        if (pChanges->getType() == WSJCppStorageChangesType::NOPE) {
            WSJCppLog::throw_err(TAG, "Not allowed use a WSJCppStorageChangesType::NOPE");
        }

        if (!pStorage->addStorageChanges(*pChanges)) {
            WSJCppLog::throw_err(TAG,"Problem add storage changes '" + pChanges->getTableName() + "' in version " + pUpdate->version());
        }
    }
}

// ---------------------------------------------------------------------

void WSJCppStorageUpdates::executeAllStorageChanges(WSJCppStorage *pStorage, WSJCppStorageConnection *pConn, WSJCppStorageUpdateBase *pUpdate) {
    std::string TAG = "StorageUpdates::executeAllStorageChanges";
    WSJCppLog::info(TAG, "Installing update '" + pUpdate->from_version() + "' -> '" + pUpdate->version() + "': " + pUpdate->description());

    // Apply changes
    std::vector<WSJCppStorageChanges *> vStorageChanges = pUpdate->getChanges();
    for (int i = 0; i < vStorageChanges.size(); i++) {
        WSJCppStorageChanges *pChanges = vStorageChanges[i];
        if (pChanges->getType() == WSJCppStorageChangesType::NOPE) {
            WSJCppLog::throw_err(TAG, "Not allowed use a WSJCppStorageChangesType::NOPE");
        }
        if (!pStorage->executeStorageChanges(pConn, *pChanges)) {
            WSJCppLog::throw_err(TAG, "Problem with table '" + pChanges->getTableName() + "' in version " + pUpdate->version());
        }
    }
    pConn->insertUpdateInfo(pUpdate->version(), pUpdate->description());
}

// ---------------------------------------------------------------------

bool WSJCppStorageUpdates::apply2(WSJCppStorage *pStorage) {
    WSJCppStorageUpdates::initGlobalVariables();
    std::string TAG = "WSJCppStorageUpdates::apply2";
    WSJCppStorageConnection *pConn = pStorage->connect();

    std::vector<std::string> vVersions = pConn->getInstalledVersions();
    std::vector<WSJCppStorageUpdateBase*> vUpdates = getSortedStorageUpdates();

    for (int i = 0; i < vUpdates.size(); i++) {
        std::string sVersion = vUpdates[i]->version();
        WSJCppStorageUpdateBase* pUpdate = vUpdates[i];
        bool bUpdatedAlreadyInstalled = std::find(vVersions.begin(), vVersions.end(), sVersion) != vVersions.end();

        if (bUpdatedAlreadyInstalled) {
            applyAllStorageChanges(pStorage, pUpdate);
        } else {
            executeAllStorageChanges(pStorage, pConn, pUpdate);
        }            
    }
    return true;
}