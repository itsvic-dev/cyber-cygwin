#include "blur.h"

class BlurPluginFactory : public KWin::EffectPluginFactory
{
    Q_OBJECT
    Q_INTERFACES(KPluginFactory)
    Q_PLUGIN_METADATA(IID KPluginFactory_iid FILE "blur.json")

public:
    explicit BlurPluginFactory();
    ~BlurPluginFactory();

    KWin::Effect *createEffect() const {
        return BlurEffect::supported() ? new BlurEffect() : nullptr;
    }
};

K_PLUGIN_FACTORY_DEFINITION(BlurPluginFactory, registerPlugin<BlurEffect>();)
K_EXPORT_PLUGIN_VERSION(KWIN_EFFECT_API_VERSION)

#include "main.moc"
