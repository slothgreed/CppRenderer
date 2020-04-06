// CGALRenderer.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include "pch.h"

using namespace KI;
int main()
{
	int NEW_SCENE = 4;
    std::cout << "Hello World!\n"; 
	std::unique_ptr<CGALRenderer> renderer(new CGALRenderer());
	auto pProject = make_shared<Project>();
	shared_ptr<IWorkspace> pWorkspace;
	if (NEW_SCENE == 1)
	{
		pWorkspace = make_shared<Workspace>();
	}
	else if(NEW_SCENE == 2)
	{
		pWorkspace = make_shared<BunnyScene>();
	}
	else if (NEW_SCENE == 3)
	{
		pWorkspace = make_shared<VoronoiScene>();
	}
	else if (NEW_SCENE == 4)
	{
		pWorkspace = make_shared<PrimitiveScene>();
	}

	renderer->Initialize();
	renderer->SetWorkspace(pWorkspace);
	pProject->Initialize();
	pWorkspace->Initialize(pProject.get());

	renderer->Run();
	
	return 0;
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
