// CGALRenderer.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include "pch.h"

using namespace KI;
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(5805);

	int NEW_SCENE = 8;
    std::cout << "Hello World!\n"; 
	OpenGLView* renderer = new OpenGLView();
	auto pProject = make_shared<Project>();
	shared_ptr<ViewViewModel> pViewViewModel;
	if (NEW_SCENE == 1)
	{
		pViewViewModel = make_shared<SampleScene>();
	}
	else if(NEW_SCENE == 2)
	{
		pViewViewModel = make_shared<BunnyScene>();
	}
	else if (NEW_SCENE == 3)
	{
		pViewViewModel = make_shared<VoronoiScene>();
	}
	else if (NEW_SCENE == 4)
	{
		pViewViewModel = make_shared<PrimitiveScene>();
	}
	else if (NEW_SCENE == 5)
	{
		pViewViewModel = make_shared<PfxScene>();
	}
	else if (NEW_SCENE == 6)
	{
		pViewViewModel = make_shared<TessellationScene>();
	}
	else if (NEW_SCENE == 7)
	{
		pViewViewModel = make_shared<RungeKuttaScene>();
	}
	else if (NEW_SCENE == 8)
	{
		pViewViewModel = make_shared<AlgorithmScene>();
	}

	renderer->Initialize();
	renderer->SetViewModel(pViewViewModel);
	pProject->Initialize();
	pViewViewModel->Initialize();

	renderer->Run();
	
	RELEASE_INSTANCE(renderer);
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
