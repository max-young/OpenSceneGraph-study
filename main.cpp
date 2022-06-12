#define GL_SILENCE_DEPRECATION

#include <osg/LOD>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

int main(int argc, char** argv)
{
  // exmpale data里没有bunny文件, 可以用其它文件代替
  // 另外, 我不知道怎么移动摄像机来改变距离
  osg::Node *model = osgDB::readNodeFile("bunny-high.ive");
  float r = model->getBound().radius();

  osg::ref_ptr<osg::LOD> root = new osg::LOD;
  root->addChild(osgDB::readNodeFile("bunny-low.ive"), r*7, FLT_MAX);
  root->addChild(osgDB::readNodeFile("bunny-mid.ive"), r*3, r*7);
  root->addChild(model, 0.0, r*3);

  osgViewer::Viewer viewer;
  viewer.setSceneData(root.get());
  return viewer.run();
}