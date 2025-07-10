#ifndef DIALOG_LOOK_UP_H
#define DIALOG_LOOK_UP_H

#include"Internal.h"

using namespace std;

struct Choice
{
	string text;
	string targetScene;
};

struct Scene
{
	string id;
	string emotion = "Non";
	vector<string> lines;
	vector<Choice> choices;
};

typedef unordered_map<std::string, Scene> SCENESTR;
typedef const string CSTR;

SCENESTR loadScenes(CSTR& filePath);

void runScriptedStory(SCENESTR& scenes, CSTR& startScene);

void SceneStart();

#endif // !DIALOG_LOOK_UP_H
