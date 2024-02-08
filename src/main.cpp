#include "utils.hpp"

class $modify(ModPauseLayer, PauseLayer) {
	static void onModify(auto& self) {
		self.setHookPriority("ModPauseLayer::customSetup", -200);
	}

	void customSetup() {
		PauseLayer::customSetup();

		auto winSize = CCDirector::get()->getWinSize();
		auto level = PlayLayer::get()->m_level;

		auto menu = this->getChildByID("left-button-menu");

		auto btn_spr = CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png");
		auto btn = CCMenuItemSpriteExtra::create(
			btn_spr,
			this,
			menu_selector(ModPauseLayer::onInfo)
		);

		btn->setID("info-button");
		btn->setPosition({menu->getContentSize().width/2, btn->getContentSize().height/2});
		menu->addChild(btn);

	}

	void onInfo(CCObject* sender) {
		auto level = PlayLayer::get()->m_level;
		std::ostringstream body;
		body << "<cg>Total Attempts:</c> " << level->m_attempts
		<< "\n<cl>Total Jumps:</c> " << level->m_jumps
		<< "\n<cy>Clicks (best att.):</c> " << level->m_clicks
		<< "\n<cr>Time (best att.):</c> " << formatTime(level->m_attemptTime);

		if (level->isPlatformer()) {
			body << "\n<cp>Best Time:</c> " << formatBestTime(level->m_bestTime)
			<< "\n<co>Best Points:</c> " << level->m_bestPoints;
		} else {
			body << "\n<cp>Normal:</c> " << level->m_normalPercent << "%"
			<< "\n<co>Practice:</c> " << level->m_practicePercent << "%";
		}

		if (level->m_levelType != GJLevelType::Editor) {
			body << "\n<cp>Objects:</c> " << level->m_objectCount
			<< "\n<cr>In Editor:</c> " << formatTime(level->m_workingTime)
			<< "\n<cr>Editor (C):</c> " << formatTime(level->m_workingTime2);
		}

		if (!level->isPlatformer() && std::string(level->m_personalBests) != "")
			body << "\n\n<cy>Progresses:</c> " << level->m_personalBests.c_str();;

		FLAlertLayer::create(
			level->m_levelName.c_str(),
			body.str(),
			"OK"
		)->show();
	}
};
