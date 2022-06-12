#define GL_SILENCE_DEPRECATION

#include <osg/Geode>
#include <osg/Geometry>
#include <osgText/Text>
#include <osgViewer/Viewer>
#include <locale.h>
#include <string>

using std::string;

void setupProperties(osgText::Text &textObject, osgText::Font *font, float size, const osg::Vec3 &pos)
{
  textObject.setFont(font);
  textObject.setCharacterSize(size);
  textObject.setPosition(pos);
  textObject.setColor(osg::Vec4(0.0, 0.0, 1.0, 1.0));
  textObject.setAlignment(osgText::Text::CENTER_BOTTOM);
  textObject.setAxisAlignment(osgText::Text::XZ_PLANE);
}

void createContent(osgText::Text &textObject, const string string)
{
  int requiredSize = std::mbstowcs(NULL, string.c_str(), 0);
  wchar_t *wtext = new wchar_t[requiredSize + 1];
  std::mbstowcs(wtext, string.c_str(), requiredSize + 1);
  textObject.setText(wtext);
  delete[] wtext;
}

int main(int argc, char **argv)
{
  setlocale(LC_ALL, "zh_CN");
  const char *titleString = "木兰辞\n拟古决绝词柬友";
  const char *textString = {
      "人生若只如初见, 何事秋风悲画扇; \n"
      "等闲变却故人心, 却道故人心易变; \n"
      "骊山语罢清宵半, 夜雨霖铃终不怨; \n"
      "何如薄幸锦衣郎, 比翼连枝当日愿; \n"};

  osgText::Font *fontHei = osgText::readFontFile("fonts/arial.ttf");
  osgText::Font *fontKai = osgText::readFontFile("fonts/times.ttf");

  osg::ref_ptr<osgText::Text> title = new osgText::Text;
  setupProperties(*title, fontHei, 20.0f, osg::Vec3(0.0f, 0.0f, 0.0f));
  createContent(*title, titleString);

  osg::ref_ptr<osgText::Text> text = new osgText::Text;
  setupProperties(*text, fontKai, 15.0f, osg::Vec3(0.0f, 0.0f, -80.0f));
  createContent(*text, textString);

  osg::ref_ptr<osg::Geode> geode = new osg::Geode;
  geode->addDrawable(osg::createTexturedQuadGeometry(
      osg::Vec3(-150.0, 1.0, -130.0), osg::Vec3(300.0, 0.0, 0.0),
      osg::Vec3(0.0, 0.0, 200.0), 1.0, 1.0));
  geode->addDrawable(title.get());
  geode->addDrawable(text.get());

  osgViewer::Viewer viewer;
  viewer.setSceneData(geode.get());
  return viewer.run();
}