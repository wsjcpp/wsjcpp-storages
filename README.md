# wsjcpp-storages

[![Build Status](https://api.travis-ci.org/wsjcpp/wsjcpp-storages.svg?branch=master)](https://travis-ci.org/wsjcpp/wsjcpp-storages) [![Github Stars](https://img.shields.io/github/stars/wsjcpp/wsjcpp-storages.svg?label=github%20%E2%98%85)](https://github.com/wsjcpp/wsjcpp-storages) [![Github Stars](https://img.shields.io/github/contributors/wsjcpp/wsjcpp-storages.svg)](https://github.com/wsjcpp/wsjcpp-storages) [![Github Forks](https://img.shields.io/github/forks/wsjcpp/wsjcpp-storages.svg?label=github%20forks)](https://github.com/wsjcpp/wsjcpp-storages/network/members)

Abstraction Model for work with different databases

## Integrate to your project

```
$ wsjcpp install https://github.com/wsjcpp/wsjcpp-storages:master
```
Or include this files:

* src.wsjcpp/wsjcpp_core/wsjcpp_core.h
* src.wsjcpp/wsjcpp_core/wsjcpp_core.cpp
* src/wsjcpp_storages.h
* src/wsjcpp_storages.cpp

For working with this abstruct modeles you need install subpackage for *-mysql or create yourself support database

Lits of supports

* will be soon

## How to use

Cheche the supporting database implementation
```
if (WsjcppStorages::support("mysql")) {
    // will support mysql database
}
```
List of implemented databases:

```
std::vector<std::string> vDbList = WsjcppStorages::list();
for (int i = 0; i < vDbList.size(); i++) {
    std::cout << vDbList[i] << std::endl;
}
```

Create instance of storage for work with database:

```
WsjcppStorage* pStorage = nullptr;
std::string sDatabaseType = "mysql";
if (WsjcppStorages::support(sDatabaseType)) {
    pStorage = WsjcppStorages::create(sDatabaseType);
    pStorage->applyConfigFromFile(sDatabaseType + ".conf"); // apply connection config
}

// now you can create a connection to database:
if (pStorage != nullptr) {
    WsjcppStorageConnection *pConnect = pStorage->connect();
}
```

Soon will be more information



