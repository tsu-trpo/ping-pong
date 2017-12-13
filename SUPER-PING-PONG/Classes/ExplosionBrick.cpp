#include "ExplosionBrick.h"
#include "DefaultMaterial.h"
#include "ObjectTags.h"
#include <iostream>

Brick* ExplosionBrick::createBrick(std::vector<Vector<Brick*>> *bricks, int newLine, int newColumn) {

    ExplosionBrick *self;
    self = new ExplosionBrick();
    self->initWithFile("res/brickRed.png");
    self->autorelease();
    self->_bricks = bricks;
    self->_line = newLine;
    self->_column = newColumn;

    auto bodySize = Size(self->getWidth(), self->getHeight());
    self->setPhysicsBody(PhysicsBody::createBox(bodySize, defaultMaterial));
    self->_physicsBody->setDynamic(false);
    self->_physicsBody->setName(brickTag);
    self->_physicsBody->setContactTestBitmask(0xffffffff);
    return self;
}

void ExplosionBrick::onContact() {
    auto temp = _bricks;

    std::cout << _line << " " << _column << " " <<  _bricks->at(6).size() << std::endl;
    for( int i = _line-1; i < _line+2; i++) {
        if(i == temp->size()) {
            std::cout << "выход" << i << std::endl;
            return;
        }

        for(int j = _column-1; j < _column + 2; j++) {
            if(j == temp->at(i).size()) {
                break;
            }
            std::cout<< "DELETE " << i << " " << j << std::endl;
            temp->at(i).at(j)->removeFromParent();
            temp->at(i).erase(j);
        }
    }
}
