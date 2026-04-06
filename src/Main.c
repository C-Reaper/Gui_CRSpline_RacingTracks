#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/Splines.h"

TransformedView tv;
CRSpline path;
Vec2* pSelected = NULL;
float Ship = 0.0f;

void Setup(AlxWindow* w){
    tv = TransformedView_Make(
        (Vec2){ GetWidth(),GetHeight() },
        (Vec2){ 0.0f,0.0f },
        (Vec2){ 0.01f,0.01f },
        (float)GetWidth() / (float)GetHeight()
    );
    
    path = (CRSpline){ Vector_New(sizeof(Vec2)) };
    for(int i = 0;i<20;i++){
        Vector_Push(&path.points,(Vec2[]){(Vec2){i*10,i*5}});
    }
}

void Update(AlxWindow* w){
    TransformedView_HandlePanZoom(&tv,w->Strokes,GetMouse());
    const Vec2 m = TransformedView_ScreenWorldPos(&tv,GetMouse());

    if(Stroke(ALX_MOUSE_L).PRESSED){
        pSelected = NULL;
        if(!pSelected) pSelected = CRSpline_Find(&path,m,1.0f);
    }
    if(Stroke(ALX_MOUSE_L).DOWN){
        if(pSelected){
            pSelected->x = m.x;
            pSelected->y = m.y;
        }
    }
    
    Clear(BLACK);

    CRSpline_Render_CP_TV(WINDOW_STD_ARGS,&tv,&path,1,RED,1.0f,WHITE);
    CRSpline_Render_GT_TV(WINDOW_STD_ARGS,&tv,&path,1,Ship,4.0f,WHITE);

    Ship += 0.1f * w->ElapsedTime;
    Ship = Ship>path.points.size?0.0f:Ship;
}

void Delete(AlxWindow* w){
    Vector_Free(&path.points);
}

int main(){
    if(Create("Splines Racing",800,600,2,2,Setup,Update,Delete))
        Start();
    return 0;
}