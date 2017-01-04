#ifndef _HL2BSPINSTANCE_H_
#define _HL2BSPINSTANCE_H_

#include "hl2bspasset.h"
#include "hl1shader.h"

#include <set>
#include <string>
#include <glm/glm.hpp>

namespace valve
{

namespace hl2
{

class BspInstance : public Hl1Instance
{
public:
    BspInstance(BspAsset* asset);
    virtual ~BspInstance();

    virtual void Update(float dt) { }
    virtual void Render(const glm::mat4& proj, const glm::mat4& view);
    void Unload();

private:
    BspAsset* _asset;
    hl1::Shader* _shader;
    std::set<unsigned short> _visibleFaces;

};

}

}

#endif // _HL2BSPINSTANCE_H_
