//
// Created by bdmr on 20/08/22.
//

#ifndef _ANIMATION_HPP_
#define _ANIMATION_HPP_

class Animation {
 public:
  enum AnimationType {spin, bounce, spinAndBounce};
 private:
  const int animationTime = 60;
  const int bounceHeight = 200;
//  Cell *c;
  AnimationType animationType;
  int time{0};
//  Point currentTranslation();
  double currentRotation();
 public:
//  Animation(Cell *cellToAnimate, AnimationType animationType)
//      : c{cellToAnimate}, animationType{animationType} {}
  void draw();
  bool isComplete();
};

void Animation::draw() {
  ++time;
//  Translation t3{currentTranslation()};
//  Rotation r{c->getCenter(), currentRotation()};
//  c->drawWithoutAnimate();
//}

//Point Animation::currentTranslation() {
//  if (animationType==bounce || animationType == spinAndBounce)
//    return {0, static_cast<int>(-1*bounceHeight*sin(3.1415*time/animationTime))};
//  else
//    return {0, 0};
}
double Animation::currentRotation() {
  if (animationType==spin || animationType == spinAndBounce)
    return time*360.0/animationTime;
  else
    return 0;
}


bool Animation::isComplete() {
  return time>60;
}


#endif //_ANIMATION_HPP_
