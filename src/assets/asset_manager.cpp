#include "debug/debug_helpers.h"

#include <nox/assets/asset.h>
#include <nox/assets/asset_manager.h>

namespace NOX {

    const std::string &AssetManager::getAssetNameFromId(AssetID id) const {
        NOX_ASSERT_IF(!assetExists(id), "Asset with given ID does not exist");
        return m_assets.find(id)->second->getName();
    }

    AssetManager::AssetID AssetManager::getAssetIdFromName(std::string_view name) const {
        const auto id = std::hash<std::string>{}(name.data());
        NOX_ASSERT_IF(!assetExists(id), "\"{0}\" asset does not exist", name);
        return id;
    }

    AssetManager::AssetID AssetManager::registerAssetFactoryImpl(std::unique_ptr<AbstractAssetFactory> &&factory) {
        const auto id = std::hash<std::string>{}(factory->getAssetName());
        if (!factoryExists(id)) {
            m_factories[id] = std::move(factory);
            NOX_DEBUG_LOG(TRACE, "\"{0}\" asset factory registered successfully", m_factories[id]->getAssetName());
        } else {
            NOX_DEBUG_LOG(WARN, "\"{0}\" asset factory already registered", m_factories[id]->getAssetName());
        }

        return id;
    }

    void AssetManager::loadAsset(AssetID id) {
        NOX_ASSERT_IF(!factoryExists(id), "Asset factory not registered for this ID");

        if (!assetExists(id)) {
            const auto &factory = m_factories[id];
            auto &asset = factory->create();
            asset->setName(factory->getAssetName());
            if (asset->isReloadable()) {
                asset->updateTimestamp();
            }
            m_assets[id] = std::move(asset);

            NOX_DEBUG_LOG(TRACE, "\"{0}\" asset loaded successfuly", m_assets[id]->getName());
        } else {
            NOX_DEBUG_LOG(WARN, "\"{0}\" asset already loaded", getAssetNameFromId(id));
        }
    }

    void AssetManager::reloadAsset(AssetID id) {
        NOX_ASSERT_IF(!assetExists(id), "Asset does not exist");
        auto &asset = m_assets[id];

        if (asset->isReloadable()) {
            if (asset->isDirty()) {
                asset->reload();
                asset->updateTimestamp();
                NOX_DEBUG_LOG(TRACE, "Asset reloaded successfully");
            } else {
                NOX_DEBUG_LOG(WARN, "Asset not modified");
            }
        } else {
            NOX_DEBUG_LOG(WARN, "Asset cannot be reloaded");
        }
    }

    std::shared_ptr<Asset> &AssetManager::getAssetImpl(AssetID id) {
        NOX_ASSERT_IF(!assetExists(id), "Asset does not exist");
        return m_assets[id];
    }

} // namespace NOX
