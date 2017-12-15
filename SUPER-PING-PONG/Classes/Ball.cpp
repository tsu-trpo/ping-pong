#include "Ball.h"
#include "AudioPlayer.h"
#include "ContactHelper.h"
#include "DefaultMaterial.h"
#include "ObjectTags.h"

Ball *Ball::createWithTexture(const std::string &textureName, Vec2 startPosition, Vec2 startVelocity)
{
    auto self = new Ball();
    self->_startVelocity = startVelocity;
    self->_startPosition = startPosition;
    // TODO: Change class CollisionStrategy
    self->_position = startPosition;
    self->_minSpeed = 600;
    self->_maxSpeed = 800;

    self->initWithFile(textureName);
    self->autorelease();

    self->setPhysicsBody(PhysicsBody::createCircle(self->getRadius(), defaultMaterial));
    self->_physicsBody->setVelocity(startVelocity);
    self->_physicsBody->setName(ballTag);
    self->_physicsBody->setContactTestBitmask(0xFFFFFFFF);

    self->_contactListener = EventListenerPhysicsContact::create();
    self->_contactListener->onContactBegin = CC_CALLBACK_1(Ball::onContact, self);
    self->getEventDispatcher()->addEventListenerWithSceneGraphPriority(self->_contactListener, self);

    return self;
}

Ball::~Ball()
{
    _eventDispatcher->removeEventListener(_contactListener);
}

void Ball::respawn()
{
    _position = _startPosition;
    _physicsBody->setVelocity(_startVelocity);
}

void Ball::setStartPosition(Vec2 newStartPosition)
{
    _startPosition = newStartPosition;
}

Vec2 Ball::getStartPosition() const
{
    return _startPosition;
}

void Ball::setStartVelocity(Vec2 newStartVelocity)
{
    _startVelocity = newStartVelocity;
}

Vec2 Ball::getStartVelocity() const
{
    return _startVelocity;
}

float Ball::getMaxSpeed() const
{
    return _maxSpeed;
}

void Ball::setMaxSpeed(float maxSpeed)
{
    _maxSpeed = maxSpeed;
}

float Ball::getMinSpeed() const
{
    return _minSpeed;
}

void Ball::setMinSpeed(float minSpeed)
{
    _minSpeed = minSpeed;
}

void Ball::setRadius(float newRadius)
{
    // из формулы radius == scale * width / 2
    // получаем: scale == radius * 2 / width
    setScale(newRadius * 2 / getContentSize().width);
}

float Ball::getRadius()
{
    return getContentSize().width * getScaleX() / 2;
}

bool Ball::onContact(PhysicsContact &contact)
{
    ContactHelper helper{contact, ballTag};
    if (!helper.wasContacted()) {
        return false;
    }

    PhysicsShape *collidedShape = helper.getOther();

    if (isTagEqualTo(collidedShape, paddleTag)) {
        auto paddle = dynamic_cast<Paddle *>(collidedShape->getBody()->getNode());
        assert(paddle);
        onContactWithPaddle(paddle);
    } else if (isTagEqualTo(collidedShape, brickTag)) {
        auto brick = dynamic_cast<Brick *>(collidedShape->getBody()->getNode());
        assert(brick);
        onContactWithBrick(brick);
    } else {
        return false;
    }
    return true;
}

void Ball::onContactWithPaddle(Paddle *paddle)
{
    // Позиция контакта относительно Paddle [-1;1]
    float relativePosition = (getPosition().x - paddle->getPosition().x) / ((paddle->getWidth() + getRadius()) / 2.0);

    // Чем ближе к краю ракетки - тем больше угол отскока и скорость шарика
    float x = relativePosition * _maxSpeed;
    float y = _minSpeed + (_maxSpeed - _minSpeed) * fabsf(relativePosition);

    getPhysicsBody()->setVelocity(Vec2(x, y));

    AudioPlayer::playEffect(AudioPlayer::hitPaddle);
}

void Ball::onContactWithBrick(Brick *brick)
{
    brick->onContact();

    AudioPlayer::playEffect(AudioPlayer::hitBrick);
}
