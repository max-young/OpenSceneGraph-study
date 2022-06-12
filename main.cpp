#define GL_SILENCE_DEPRECATION

#include <osg/AutoTransform>
#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

// 始终面对屏幕
osg::Transform* createAutoTransform(double posX, osg::Node *model)
{
  osg::ref_ptr<osg::AutoTransform> at = new osg::AutoTransform;
  at->setAutoRotateMode(osg::AutoTransform::ROTATE_TO_SCREEN);
  at->setPosition(osg::Vec3(posX, 0.0, 0.0));
  at->addChild(model);
  return at.release();
}

// 延Z轴逆时针旋转45度
osg::Transform* createMatrixTransform(double posX, double rotateZ, osg::Node *model)
{
  osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform;
  mt->setMatrix(osg::Matrix::rotate(rotateZ, osg::Z_AXIS) * osg::Matrix::translate(posX, 0.0, 0.0));
  mt->addChild(model);
  return mt.release();
}

// 延Z轴顺时针旋转45度
osg::Transform* createPositionAttitudeTransform(double posX, double rotateZ, osg::Node *model)
{
  osg::ref_ptr<osg::PositionAttitudeTransform> pat = new osg::PositionAttitudeTransform;
  pat->setPosition(osg::Vec3(posX, 0.0, 0.0));
  pat->setAttitude(osg::Quat(rotateZ, osg::Z_AXIS));
  pat->addChild(model);
  return pat.release();
}

int main(int argc, char** argv)
{
  osg::ArgumentParser arguments(&argc, argv);
  osg::Node *model = osgDB::readNodeFiles(arguments);
  if (!model) model = osgDB::readNodeFile("axes.osgt");

  osg::ref_ptr<osg::Group> root = new osg::Group;
  root->addChild(createMatrixTransform(-5.0, osg::PI/4, model));
  root->addChild(createAutoTransform(0.0, model));
  root->addChild(createPositionAttitudeTransform(5.0, -osg::PI/4, model));

  osgViewer::Viewer viewer;
  viewer.setSceneData(root.get());
  return viewer.run();
}