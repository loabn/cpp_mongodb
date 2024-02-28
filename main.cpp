#include <algorithm>
#include <iostream>
#include <vector>

// MongoDB
#include <mongocxx/client.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>

static const mongocxx::uri mongoURI = mongocxx::uri { "mongodb://localhost:27017" };

std::vector<std::string> getDatabases(mongocxx::client& client) {
    return client.list_database_names();
}

void createCollection(mongocxx::database& db, const std::string& collectionName) {
    db.create_collection(collectionName);
}

bsoncxx::document::value createDocument(const std::vector<std::pair<std::string, std::string>>& keyValues) {
    bsoncxx::builder::stream::document document{};

    for(auto& keyValue : keyValues) {
        document << keyValue.first << keyValue.second;
    }

    return document << bsoncxx::builder::stream::finalize;
}

void insertDocument(mongocxx::collection& collection, const bsoncxx::document::value& document) {
    collection.insert_one(document.view());
}

void printCollection(mongocxx::collection& collection) {
    if (collection.count_documents({}) == 0) {
        std::cout << "Collection is empty." << std::endl;
        return;
    }

    auto cursor = collection.find({});

    for (auto&& doc : cursor) {
        std::cout << bsoncxx::to_json(doc) << std::endl;
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    mongocxx::instance instance{};
    mongocxx::options::client clientOptions;

    auto api = mongocxx::options::server_api{ mongocxx::options::server_api::version::k_version_1 };
    clientOptions.server_api_opts(api);

    mongocxx::client conn{ mongoURI, clientOptions };

    auto dbs = getDatabases(conn);

    for (const auto& db : dbs) {
        std::cout << db << std::endl;
    }

    return EXIT_SUCCESS;
}
