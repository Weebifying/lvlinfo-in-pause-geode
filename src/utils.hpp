#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;

std::string formatBestTime(int time) {
	std::ostringstream ftime;
	if (time / 3600000 >= 1) {
		ftime << (int)time/3600000 << ":";
		time -= ((int)time/3600000)*3600000;
	}
	if (time / 60000 >= 1) {
		ftime << (int)time/60000 << ":";
		time -= ((int)time/60000)*60000;
	}

	ftime << (int)time/1000 << ".";
	time -= ((int)time/1000)*1000;
	ftime << time;
	return ftime.str();
}

std::string formatTime(int time) {
    std::ostringstream ftime;
    if (time / 3600 >= 1) {
		ftime << (int)time/3600 << "h";
		time -= ((int)time/3600)*3600;
	}
	if (time / 60 >= 1) {
		ftime << (int)time/60 << "m";
		time -= ((int)time/60)*60;
	}

	ftime << time << "s";
	return ftime.str();
}