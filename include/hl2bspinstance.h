#ifndef _HL2BSPINSTANCE_H_
#define _HL2BSPINSTANCE_H_

#include "hl2bspasset.h"
#include "hl2bspshader.h"

#include <set>
#include <string>
#include <glm/glm.hpp>

class Hl2BspInstance : public Hl1Instance
{
    friend class Hl2BspAsset;
    Hl2BspInstance(Hl2BspAsset* asset);
public:
    virtual ~Hl2BspInstance();

    virtual void Update(float dt) { }
    virtual void Render(const glm::mat4& proj, const glm::mat4& view);
    void Unload();

private:
    Hl2BspAsset* _asset;
    Hl1Shader* _shader;
    std::set<unsigned short> _visibleFaces;

};

#endif // _HL2BSPINSTANCE_H_

