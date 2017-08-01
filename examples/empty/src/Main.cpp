# include <Siv3D.hpp> // OpenSiv3D v0.1.5

void Main()
{
    Window::Resize(800, 450);
    
    const Texture chimpan(L"../Pictures/animal_chimpanzee.png");
    const Texture bgSchool(L"../Pictures/bg_school.jpg");
    const Texture parts_tanni(L"../Pictures/tanni.png");
    
    Array<Circle> tni;
    
    const Font titlefont(50);
    const Font scorefont(30);
    const Font timefont(25);
    const Font tfont(20);
    
    int score = 0;
    double time = 30.0;
    
    enum Scene{
        TITLE,
        MAIN,
        RESULT
    };
    
    Scene scene = TITLE;

	while (System::Update())
	{
        bgSchool.resize(800, 450).draw(0, 0);
        
        if(scene == TITLE){
            titlefont(L"単位キャッチャー").drawAt(Window::Width() / 2,150,Palette::Black);
            if(MouseL.pressed()){
                time = 30.0;
                scene = MAIN;
            }
            continue;
        }
        else if(scene == RESULT){
            scorefont(L"修得単位数:",score).drawAt(Window::Width() / 2,150,Palette::Black);
            if(MouseL.pressed()){
                time = 30.0;
                scene = MAIN;
            }
            continue;
        }
        
        time -= System::DeltaTime();
        if(time <= 0){
            scene = RESULT;
        }
        
        timefont(L"残り時間:",(int)time).drawAt(150,50,Palette::Black);
        
        chimpan.scale(0.1).drawAt(Cursor::Pos().x,400);

        if(System::FrameCount() % 25 == 0){
            tni.push_back(Circle(Random(0,Window::Width()), 0, 30));
        }
        
        for(auto &t:tni){
            t.moveBy(0, 10);
            t.draw(Palette::Blue);
            tfont(L"単位").drawAt(t.x,t.y);
        }
        
        Erase_if(tni, [&](Circle t){
            if(t.intersectsAt(chimpan.scale(0.1).regionAt(Cursor::Pos().x,400))){
                score++;
                return true;
            }
            else{
                return false;
            }
        });
	}
}
