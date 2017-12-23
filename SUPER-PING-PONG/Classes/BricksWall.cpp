#include "BricksWall.h"
#include "VisibleRect.h"

void BricksWall::createBricks(int lines, int columns, GameScene *Scene)
{
    _bricks = std::vector<Vector<Brick *>>(lines);
    float center = VisibleRect::center().x;
    float top = VisibleRect::top().y;

    float widthBrick = 90;
    float heightBrick = 35;

    float halfLine = (columns / 2.0) * widthBrick;
    float beginLine = center - halfLine + widthBrick / 2;
    float offsetTop = 1.5 * heightBrick;
    float y = top - offsetTop + heightBrick / 2;

    for (int i = 0; i < lines; i++) {
        float x = beginLine;
        for (int j = 0; j < columns; j++) {
            int type = rand() % 3;
            Brick *brick = BrickFactory::createBrick(type, &_bricks, i, j);
            brick->setWidth(widthBrick);
            brick->setHeight(heightBrick);
            brick->setPosition(x, y);
            Scene->addChild(brick);
            _bricks.at(i).pushBack(brick);
            x += widthBrick;
        }
        y -= heightBrick;
    }
}
