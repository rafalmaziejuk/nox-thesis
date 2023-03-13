#pragma once

#include <nox/assets/asset_factory.h>

#include <unordered_map>

namespace NOX {

    class AssetManager {
        using AssetID = size_t;
        using AssetFactoryMap = std::unordered_map<AssetID, std::unique_ptr<AbstractAssetFactory>>;
        using AssetHandleMap = std::unordered_map<AssetID, std::shared_ptr<Asset>>;

      public:
        template <typename T, typename... Args>
        AssetID registerAssetFactory(std::string_view name, Args &&...args) {
            return registerAssetFactoryImpl(createFactory<T>(name, std::forward<Args>(args)...));
        }

        template <typename T, typename... Args>
        std::shared_ptr<T> loadAssetImmediate(std::string_view name, Args &&...args) {
            const auto id = registerAssetFactoryImpl(createFactory<T>(name, std::forward<Args>(args)...));
            loadAsset(id);
            return getAsset<T>(id);
        }

        template <typename T>
        std::shared_ptr<T> getAsset(AssetID id) {
            return std::dynamic_pointer_cast<T>(getAssetImpl(id));
        }

        const std::string &getAssetNameFromId(AssetID id) const;
        AssetID getAssetIdFromName(std::string_view name) const;

        bool factoryExists(AssetID id) const { return (m_factories.find(id) != m_factories.end()); }
        bool assetExists(AssetID id) const { return (m_assets.find(id) != m_assets.end()); }

        void loadAsset(AssetID id);
        void reloadAsset(AssetID id);

      private:
        AssetID registerAssetFactoryImpl(std::unique_ptr<AbstractAssetFactory> &&factory);
        std::shared_ptr<Asset> &getAssetImpl(AssetID id);

      private:
        AssetFactoryMap m_factories;
        AssetHandleMap m_assets;
    };

} // namespace NOX
