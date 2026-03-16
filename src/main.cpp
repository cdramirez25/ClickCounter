#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>

using namespace geode::prelude;

class $modify(MyPlayLayer, PlayLayer) {

    struct Fields {
        int m_clicks = 0;
        CCLabelBMFont* m_label = nullptr;
    };

    void updateLabel() {
        if (!m_fields->m_label) return;
        m_fields->m_label->setString(
            fmt::format("CC: {}", m_fields->m_clicks).c_str()
        );
    }

    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects))
            return false;

        auto winSize = CCDirector::get()->getWinSize();

        auto label = CCLabelBMFont::create("CC: 0", "bigFont.fnt");
        label->setScale(0.45f);
        label->setOpacity(150);
        label->setAnchorPoint({ 0.f, 1.f });
        label->setPosition({ 6.f, winSize.height - 6.f });
        label->setZOrder(100);

        this->m_uiLayer->addChild(label);

        m_fields->m_label = label;

        return true;
    }

    void onQuit() {
        PlayLayer::onQuit();
    }

    void resetLevel() {
        m_fields->m_clicks = 0;
        updateLabel();
        PlayLayer::resetLevel();
    }
};

class $modify(MyBaseLayer, GJBaseGameLayer) {

    void handleButton(bool down, int button, bool isPlayer1) {
        GJBaseGameLayer::handleButton(down, button, isPlayer1);
        if (!down) return;
        auto pl = PlayLayer::get();
        if (!pl) return;
        auto myPl = static_cast<MyPlayLayer*>(pl);
        myPl->m_fields->m_clicks++;
        myPl->updateLabel();
    }
};