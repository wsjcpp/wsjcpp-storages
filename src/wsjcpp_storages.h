#ifndef WSJCPP_STORAGES_H
#define WSJCPP_STORAGES_H

#include <map>
#include <string>
#include <vector>
#include <wsjcpp_core.h>

#include <string>
#include <vector>
#include <map>

// ---------------------------------------------------------------------

enum WSJCppStorageColumnType {
    DATETIME,
    STRING,
    NUMBER,
    DOUBLE_NUMBER
};

// TODO cast to string

// ---------------------------------------------------------------------

class WSJCppStorageColumnDef {
    public:
        WSJCppStorageColumnDef(const std::string &sColumnName);
        WSJCppStorageColumnDef &autoIncrement();
        WSJCppStorageColumnDef &notNull();
        WSJCppStorageColumnDef &string(int nSize);
        WSJCppStorageColumnDef &text();
        WSJCppStorageColumnDef &datetime();
        WSJCppStorageColumnDef &number();
        WSJCppStorageColumnDef &doubleNumber();
        WSJCppStorageColumnDef &primaryKey();
        WSJCppStorageColumnDef &defaultValue(const std::string& sDefault);
        WSJCppStorageColumnDef &enableIndex();
        WSJCppStorageColumnDef &enableUniqueIndex(const std::string& sIndexName);

        std::string columnName() const;
        std::string columnType();
        bool isDefaultValue();
        std::string columnDefaultValue();

        int columnTypeSize();
        bool isAutoIncrement();
        bool isPrimaryKey();
        bool isNotNull();
        bool isEnableIndex();
        bool isEnableUniqueIndex();
        std::string nameOfUniqueIndex();

    private:
        std::string TAG;
        std::string m_sColumnName;
        std::string m_sType;
        std::string m_sDefaultValue;
        int m_nTypeSize;

        bool m_bAutoIncrement;
        bool m_bNotNull;
        bool m_bPrimaryKey;
        bool m_bDefaultValue;
        bool m_bEnableIndex;
        bool m_bEnableUniqueIndex;
        std::string m_sNameOfUniqueIndex;
};

// ---------------------------------------------------------------------

// TODO redesign

class WSJCppStorageColumnDefIndex {

};

// ---------------------------------------------------------------------

enum WSJCppStorageChangesType {
    NOPE,
    DROP_TABLE,
    MODIFY_TABLE,
    CREATE_TABLE,
    INSERT_ROW,
    DELETE_ROW,
    UPDATE_ROW,
    SELECT_ROWS
};

// ---------------------------------------------------------------------

class WSJCppStorageChanges {
    public:
        WSJCppStorageChanges(const std::string &sTableName);
        std::string getTableName() const;
        virtual WSJCppStorageChangesType getType() const;
        virtual std::string getStartApply() const;
        virtual std::string getAppliedSuccess() const;
        virtual std::string getAppliedFailed() const;

    protected:
        std::string TAG;
        std::string m_sTableName;
};

// ---------------------------------------------------------------------

class WSJCppStorageCreateTable : public WSJCppStorageChanges {
    public:
        WSJCppStorageCreateTable(const std::string &sTableName);
        virtual WSJCppStorageChangesType getType() const override;
        virtual std::string getStartApply() const override;
        virtual std::string getAppliedSuccess() const override;
        virtual std::string getAppliedFailed() const override;

        WSJCppStorageColumnDef &addColumn(const std::string &sColumnName);
        const std::vector<WSJCppStorageColumnDef> &getColumns() const;

    private:
        std::string TAG;
        std::string m_sTableName;
        std::vector<WSJCppStorageColumnDef> m_vColumns;
};

// ---------------------------------------------------------------------

class WSJCppStorageModifyTable : public WSJCppStorageChanges {
    public:
        WSJCppStorageModifyTable(const std::string &sTableName);
        virtual WSJCppStorageChangesType getType() const override;
        virtual std::string getStartApply() const override;
        virtual std::string getAppliedSuccess() const override;
        virtual std::string getAppliedFailed() const override;

        WSJCppStorageColumnDef &addColumn(const std::string &sColumnName);
        WSJCppStorageColumnDef &alterColumn(const std::string &sColumnName);
        std::string dropColumn(const std::string &sColumnName);
        const std::vector<WSJCppStorageColumnDef> &getAddColumns() const;
        const std::vector<WSJCppStorageColumnDef> &getAlterColumns() const;
        const std::vector<std::string> &getDropColumns() const;
        bool isColumnDefined(const std::string &sColumnName, std::string &sError) const;

    private:
        std::string TAG;
        std::string m_sTableName;
        std::vector<WSJCppStorageColumnDef> m_vAddColumns;
        std::vector<WSJCppStorageColumnDef> m_vAlterColumns;
        std::vector<std::string> m_vDropColumns;
};

// ---------------------------------------------------------------------

class WSJCppStorageDropTable : public WSJCppStorageChanges {
    public:
        WSJCppStorageDropTable(const std::string &sTableName);
        virtual WSJCppStorageChangesType getType() const override;
        virtual std::string getStartApply() const override;
        virtual std::string getAppliedSuccess() const override;
        virtual std::string getAppliedFailed() const override;

    private:
        std::string TAG;
        std::string m_sTableName;
};

// ---------------------------------------------------------------------

class WSJCppStorageColumnValue {
    public:
        WSJCppStorageColumnValue(const std::string &sColumnName, WSJCppStorageColumnType nType);
        void setValue(std::string sValue);
        void setValue(int nValue);
        void setValue(double nValue);
        std::string getColumnName();
        WSJCppStorageColumnType getColumnType();
        std::string getString();
        int getInt();
        double getDouble();

    private:
        std::string m_sColumnName;
        WSJCppStorageColumnType m_nColumnType;

        std::string m_sStringValue;
        int m_nIntValue;
        double m_nDoubleValue;
};

// ---------------------------------------------------------------------

class WSJCppStorageTable {
    public:
        WSJCppStorageTable(const std::string &sTableName);
        WSJCppStorageTable(WSJCppStorageCreateTable &createTable);
        std::string getTableName() const;
        const std::vector<WSJCppStorageColumnDef> &getColumns() const;
        void mergeWith(WSJCppStorageModifyTable &modifyTable);
        
    private:
        std::string TAG;
        std::string m_sTableName;
        std::vector<WSJCppStorageColumnDef> m_vColumns;
};

// ---------------------------------------------------------------------

class WSJCppStorageInsert : public WSJCppStorageChanges {
    public:
        WSJCppStorageInsert(const std::string &sTableName);
        virtual WSJCppStorageChangesType getType() const override;
        virtual std::string getStartApply() const override;
        virtual std::string getAppliedSuccess() const override;
        virtual std::string getAppliedFailed() const override;

        void bindValue(const std::string &sColumnName, const std::string &sValue);
        void bindValue(const std::string &sColumnName, int nValue);
        void bindValue(const std::string &sColumnName, double nValue);
        std::vector<WSJCppStorageColumnValue> values() const;
        bool isValid(const WSJCppStorageTable &storageTable) const;

    private:
        bool exists(const std::string &sColumnName);
        std::string TAG;
        std::string m_sTableName;
        std::vector<WSJCppStorageColumnValue> m_vValues;
};

// ---------------------------------------------------------------------

/*
class StorageUpdate {
    public:
        StorageUpdate(const StorageStruct &storageStruct);
        std::string tableName() const;
        void bindValue(const std::string &sColumnName, const std::string &sValue);
        void bindValue(const std::string &sColumnName, int nValue);
        void bindValue(const std::string &sColumnName, double nValue);
        std::vector<StorageColumnValue> values() const;
        bool isValid() const;
    private:
        StorageStruct m_storageStruct;
        bool exists(const std::string &sColumnName);
        std::string TAG;
        std::string m_sTableName;
        std::vector<StorageColumnValue> m_vValues;
};
*/

// ---------------------------------------------------------------------

class WSJCppStorageConnection {
    public:
        WSJCppStorageConnection();
        virtual ~WSJCppStorageConnection();
        virtual bool executeQuery(const std::string &sQuery) = 0; // TODO redesign in future
        virtual std::string lastDatabaseVersion() = 0;
        virtual std::vector<std::string> getInstalledVersions() = 0;
        virtual bool insertUpdateInfo(const std::string &sVersion, const std::string &sDescription) = 0;
        
        long created();
        long getConnectionDurationInSeconds();

    protected:
        std::string TAG;

    private:
        long m_nCreated;
};

// ---------------------------------------------------------------------

class WSJCppStorage {
    public:
        WSJCppStorage();
        // WSJCppStorage(const std::string &sType);
        static std::string type() { return "unknown"; };
        virtual bool applyConfigFromFile(const std::string &sFilePath) = 0;
        virtual WSJCppStorageConnection *connect() = 0;
        virtual void clean() = 0;
        virtual std::string prepareStringValue(const std::string &sValue) = 0;

        // virtual std::vector<std::string> prepareSqlQueries(StorageStruct &storageStruct) = 0; // TODO deprecated

        bool executeStorageChanges(WSJCppStorageConnection *pConn, WSJCppStorageChanges &storageChanges);
        bool addStorageChanges(WSJCppStorageChanges &storageChanges);

        virtual std::vector<std::string> prepareSqlQueries(const WSJCppStorageInsert &storageInsert) = 0;
        virtual std::vector<std::string> prepareSqlQueries(const WSJCppStorageCreateTable &storageCreateTable) = 0;
        virtual std::vector<std::string> prepareSqlQueries(const WSJCppStorageModifyTable &storageModifyTable) = 0;
        virtual std::vector<std::string> prepareSqlQueries(const WSJCppStorageDropTable &storageDropTable) = 0;
        
        bool insertRow(WSJCppStorageConnection *pConn, const WSJCppStorageInsert &storageInsert);
        const std::map<std::string, WSJCppStorageTable> &getTables();
        bool existsTable(const std::string &sTableName);
        const WSJCppStorageTable &getTableDef(const std::string &sTableName);

    protected:
        std::string TAG;

    private:
        std::map<std::string, WSJCppStorageTable> m_mapTables;
};

// ---------------------------------------------------------------------

class IFabricWSJCppStorage {
    public:
        virtual WSJCppStorage *create() = 0;
};

// ---------------------------------------------------------------------

extern std::map<std::string, IFabricWSJCppStorage*> *g_pFabricWSJCppStorages;

class WSJCppStorages {
    public:
        static void initGlobalVariables();
        static void add(const std::string &sType, IFabricWSJCppStorage* pStorage);
        static std::vector<std::string> list();
        static bool support(const std::string &sType);
        static WSJCppStorage* create(const std::string &sType);
};

// ---------------------------------------------------------------------

template<class T>
class FabricWSJCppStorage : IFabricWSJCppStorage {
    public:
        FabricWSJCppStorage() {
            WSJCppStorages::add(T::type(), this);
        };
        virtual WSJCppStorage *create() {
            return new T();
        };
};

// ---------------------------------------------------------------------
// RegistryStorage
#define REGISTRY_STORAGE( classname ) \
    static FabricWSJCppStorage<classname> * pRegistryFabric ## classname = new FabricWSJCppStorage<classname>(); \

// ---------------------------------------------------------------------

class WSJCppStorageUpdateBase {

    public:
        WSJCppStorageUpdateBase(const std::string &sFromVersion, const std::string &sVersion, const std::string &sDescription);
        const std::string &from_version();
        const std::string &version();
        const std::string &description();
        const std::vector<WSJCppStorageChanges *> &getChanges();
        void setWeight(int nWeight);
        int getWeight();
    protected:
        std::string TAG;
        WSJCppStorageCreateTable *createTable(std::string sTableName);
        WSJCppStorageModifyTable *modifyTable(std::string sTableName);
        WSJCppStorageDropTable *dropTable(std::string sTableName);
        WSJCppStorageInsert *insertIntoTable(std::string sTableName);
        
    private:
        void checkTableName(std::string sTableName);
        std::vector<WSJCppStorageChanges *> m_vStorageChanges;
        std::string m_sFromVersion;
        std::string m_sVersion;
        std::string m_sDescription;
        int m_nWeight;
};

// ---------------------------------------------------------------------

extern std::vector<WSJCppStorageUpdateBase *> *g_pWSJCppStorageUpdates;

class WSJCppStorageUpdates {
    private:
        static int calculateWeight(int nWeight, const std::string &sVersion);
        static void sortByWeight(std::vector<WSJCppStorageUpdateBase*> &vUpdates);
        static std::vector<WSJCppStorageUpdateBase*> findUpdatesFromVersion(const std::string &sVersion);
        static void pushUpdatesFromVersion(std::vector<WSJCppStorageUpdateBase*> &vUpdates, const std::string &sVersion);
        static void applyAllStorageChanges(WSJCppStorage *pStorage, WSJCppStorageUpdateBase *pUpdate);
        static void executeAllStorageChanges(WSJCppStorage *pStorage, WSJCppStorageConnection *pConn, WSJCppStorageUpdateBase *pUpdate);

    public:
        static std::vector<WSJCppStorageUpdateBase*> getSortedStorageUpdates();
        static void initGlobalVariables();
        static WSJCppStorageUpdateBase* findUpdateFromVersion(const std::string &sFromVersion);
        static WSJCppStorageUpdateBase* findUpdateVersion(const std::string &sVersion);
        // static bool apply(Storage *pStorage);
        static bool apply2(WSJCppStorage *pStorage);
};

// ---------------------------------------------------------------------

// RegistryCmdHandler
#define REGISTRY_STORAGE_UPDATE( classname ) \
    static classname * pRegistry ## classname = new classname();


#endif // WSJCPP_STORAGES_H