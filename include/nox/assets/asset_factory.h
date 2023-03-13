#pragma once

#include <memory>
#include <string_view>

namespace NOX {

    class Asset;

    class AbstractAssetFactory {
      public:
        virtual ~AbstractAssetFactory() = default;

        virtual std::shared_ptr<Asset> create() const = 0;
        virtual std::string getAssetName() const = 0;
    };

    template <typename T, typename... Args>
    class AssetFactory : public AbstractAssetFactory {
        using Arguments = std::tuple<std::decay_t<Args>...>;

      public:
        AssetFactory(std::string_view assetName, Args &&...args) : m_assetName(assetName),
                                                                   m_arguments(std::forward<Args>(args)...) {}
        ~AssetFactory() override = default;

        std::shared_ptr<Asset> create() const override {
            return std::apply([](auto &&...args) { return T::create(std::forward<decltype(args)>(args)...); }, m_arguments);
        }

        std::string getAssetName() const override { return m_assetName; }

      private:
        std::string m_assetName;
        Arguments m_arguments;
    };

    template <typename T, typename... Args>
    inline auto createFactory(std::string_view assetName, Args &&...args) {
        return std::make_unique<AssetFactory<T, Args...>>(assetName, std::forward<Args>(args)...);
    }

} // namespace NOX
