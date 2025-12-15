#pragma once

struct BreakEffect 
{
    bool active;
    float x, y;
    int currentFrame;
    int frameTimer;
    int timer;
};

void UpdateBreakEffects(BreakEffect effects[16]);
void DrawBreakEffects(BreakEffect effects[16], float scrollX, int breakImg);
