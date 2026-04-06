#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/Splines.h"

#define NODES_COUNT 20
#define TRACK_R     5.0f

TransformedView tv;
CRSpline path;
CRSpline_DP dps;
Vec2* pSelected = NULL;
float Ship = 0.0f;
float Step = 1.0f;

void Setup(AlxWindow* w){
    tv = TransformedView_Make(
        (Vec2){ GetWidth(),GetHeight() },
        (Vec2){ 0.0f,0.0f },
        (Vec2){ 0.01f,0.01f },
        (float)GetWidth() / (float)GetHeight()
    );
    
    path = CRSpline_New();
    for(int i = 0;i<NODES_COUNT;i++){
        const float a = (float)i / (float)NODES_COUNT * F32_PI2;
        const float x = cosf(a) * 100.0f;
        const float y = sinf(a) * 100.0f;
        Vector_Push(&path.points,(Vec2[]){ x,y });
    }
    
    dps = CRSpline_DP_Make(NODES_COUNT);
    memset(dps.Memory,0,sizeof(float) * NODES_COUNT);
    dps.size = NODES_COUNT;
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

    if(Stroke(ALX_KEY_UP).DOWN)     Step *= 1.01f;
    if(Stroke(ALX_KEY_DOWN).DOWN)   Step *= 0.99f;

    memset(dps.Memory,0,sizeof(float) * NODES_COUNT);
    //CRSpline_Path_Min(&path,&dps,1,TRACK_R,(int)ceilf(Step),0.3f);
    //CRSpline_Path_Max(&path,&dps,1,TRACK_R,(int)ceilf(Step),0.3f);
    CRSpline_Path_MinCv(&path,&dps,1,TRACK_R,(int)ceilf(Step),0.3f);

    Clear(BLACK);

    CRSpline so = CRSpline_New_Offset(&path,1, TRACK_R);
    CRSpline si = CRSpline_New_Offset(&path,1,-TRACK_R);
    CRSpline rl = CRSpline_New_DP(&path,1,&dps);
    

    //CRSpline_Render_CP_TV(WINDOW_STD_ARGS,&tv,&path,1,RED,1.0f,WHITE);
    CRSpline_Render_CP_TV(WINDOW_STD_ARGS,&tv,&rl,1,BLUE,1.0f,WHITE);

    CRSpline_Render_CP_TV(WINDOW_STD_ARGS,&tv,&so,1,RED,1.0f,WHITE);
    CRSpline_Render_CP_TV(WINDOW_STD_ARGS,&tv,&si,1,RED,1.0f,WHITE);
    
    //CRSpline_Render_GT_TV(WINDOW_STD_ARGS,&tv,&path,1,Ship,4.0f,WHITE);
    CRSpline_Render_GT_TV(WINDOW_STD_ARGS,&tv,&rl,1,Ship,4.0f,WHITE);

    CStr_RenderAlxFontf(WINDOW_STD_ARGS,GetAlxFont(),0.0f,0.0f,RED,"S: %f",Step);


    Ship += 0.1f * w->ElapsedTime;
    Ship = Ship>path.points.size?0.0f:Ship;

    CRSpline_Free(&rl);
    CRSpline_Free(&si);
    CRSpline_Free(&so);
}

void Delete(AlxWindow* w){
    CRSpline_Free(&path);
}

int main(){
    if(Create("Splines Racing",800,600,2,2,Setup,Update,Delete))
        Start();
    return 0;
}