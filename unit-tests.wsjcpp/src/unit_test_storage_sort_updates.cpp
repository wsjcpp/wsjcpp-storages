#include "unit_test_storage_sort_updates.h"
#include <wsjcpp_storages.h>

REGISTRY_UNIT_TEST(UnitTestStorageSortUpdates)

UnitTestStorageSortUpdates::UnitTestStorageSortUpdates() 
    : UnitTestBase("UnitTestStorageSortUpdates") {
    // 
}

// ---------------------------------------------------------------------

void UnitTestStorageSortUpdates::init() {
}

// ---------------------------------------------------------------------

bool UnitTestStorageSortUpdates::run() {
    // WSJCppStorage *pStorage = WSJCppStorages::create("mysql");
    bool bTestSuccess = true;
    std::vector<WSJCppStorageUpdateBase *> vUpdates;
    vUpdates.push_back(new WSJCppStorageUpdateBase("", "u0001", "null -> 1"));
    vUpdates.push_back(new WSJCppStorageUpdateBase("u0001", "u0002", "1 -> 2"));
    vUpdates.push_back(new WSJCppStorageUpdateBase("u0002", "u0003", "2 -> 3"));
    vUpdates.push_back(new WSJCppStorageUpdateBase("u0003", "u1004", "3 -> 1004"));
    vUpdates.push_back(new WSJCppStorageUpdateBase("u0003", "u0005", "3 -> 5"));
    vUpdates.push_back(new WSJCppStorageUpdateBase("u0005", "u0006", "5 -> 6"));
    vUpdates.push_back(new WSJCppStorageUpdateBase("u0006", "u0007", "6 -> 7"));
    vUpdates.push_back(new WSJCppStorageUpdateBase("u1004", "u1005", "1004 -> 1005"));
    vUpdates.push_back(new WSJCppStorageUpdateBase("u0007", "u0008", "7 -> 8"));
    vUpdates.push_back(new WSJCppStorageUpdateBase("u0008", "u0009", "8 -> 9"));
    vUpdates.push_back(new WSJCppStorageUpdateBase("u0009", "u0010", "9 -> 10"));
    vUpdates.push_back(new WSJCppStorageUpdateBase("u0010", "u0011", "10 -> 11"));
    vUpdates.push_back(new WSJCppStorageUpdateBase("u0011", "u0012", "11 -> 12"));
    vUpdates.push_back(new WSJCppStorageUpdateBase("u0012", "u0013", "12 -> 13"));
    vUpdates.push_back(new WSJCppStorageUpdateBase("u0013", "u0014", "13 -> 14"));
    vUpdates.push_back(new WSJCppStorageUpdateBase("u0010", "u1011", "10 -> 1011"));
    vUpdates.push_back(new WSJCppStorageUpdateBase("u1011", "u1012", "1011 -> 1012"));
    vUpdates.push_back(new WSJCppStorageUpdateBase("u0014", "u1015", "14 -> 1015"));
    vUpdates.push_back(new WSJCppStorageUpdateBase("u0014", "u0015", "14 -> 15"));
    vUpdates.push_back(new WSJCppStorageUpdateBase("u0015", "u0016", "15 -> 16"));
    vUpdates.push_back(new WSJCppStorageUpdateBase("u0014", "u1016", "14 -> 1016"));
    

    std::vector<std::string> vUpdatesExpectedSorted;
    vUpdatesExpectedSorted.push_back("-u0001");
    vUpdatesExpectedSorted.push_back("u0001-u0002");
    vUpdatesExpectedSorted.push_back("u0002-u0003");
    vUpdatesExpectedSorted.push_back("u0003-u1004");
    vUpdatesExpectedSorted.push_back("u1004-u1005");
    vUpdatesExpectedSorted.push_back("u0003-u0005");
    vUpdatesExpectedSorted.push_back("u0005-u0006");
    vUpdatesExpectedSorted.push_back("u0006-u0007");
    vUpdatesExpectedSorted.push_back("u0007-u0008");
    vUpdatesExpectedSorted.push_back("u0008-u0009");
    vUpdatesExpectedSorted.push_back("u0009-u0010");
    vUpdatesExpectedSorted.push_back("u0010-u1011");
    vUpdatesExpectedSorted.push_back("u1011-u1012");
    vUpdatesExpectedSorted.push_back("u0010-u0011");
    vUpdatesExpectedSorted.push_back("u0011-u0012");
    vUpdatesExpectedSorted.push_back("u0012-u0013");
    vUpdatesExpectedSorted.push_back("u0013-u0014");
    vUpdatesExpectedSorted.push_back("u0014-u1015");
    vUpdatesExpectedSorted.push_back("u0014-u1016");
    vUpdatesExpectedSorted.push_back("u0014-u0015");
    vUpdatesExpectedSorted.push_back("u0015-u0016");

    std::vector<WSJCppStorageUpdateBase*> vUpdatesSorted = WSJCppStorageUpdates::getSortedStorageUpdates();

    compareN(bTestSuccess, "vUpdates.size() == vUpdatesExpectedSorted.size()", vUpdates.size(), vUpdatesExpectedSorted.size());
    compareN(bTestSuccess, "vUpdates.size() == vUpdatesSorted.size()", vUpdates.size(), vUpdatesSorted.size());
    if (!bTestSuccess) {
        return bTestSuccess;
    }

    for (int i = 0; i < vUpdatesSorted.size(); i++) {
        WSJCppStorageUpdateBase* pUpdate = vUpdatesSorted[i];
        std::string sUpdateId = pUpdate->from_version() + "-" + pUpdate->version();
        std::string sUpdateIdExpected = vUpdatesExpectedSorted[i];
        compareS(bTestSuccess, "check update sort", sUpdateId, sUpdateIdExpected);
    }
    return bTestSuccess;
}

// ---------------------------------------------------------------------