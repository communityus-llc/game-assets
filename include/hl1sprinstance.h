#ifndef _HL1SPRINSTANCE_H
#define _HL1SPRINSTANCE_H

#include "hl1sprasset.h"
#include "hl1sprshader.h"

class Hl1SprInstance : public Hl1Instance
{
    friend class Hl1SprAsset;
    Hl1SprInstance(Hl1SprAsset* asset);
public:
    virtual ~Hl1SprInstance();

    virtual void Update(float dt);
    virtual void Render(const glm::mat4& proj, const glm::mat4& view);
    void Unload();

private:
    Hl1SprAsset* _asset;
    Hl1SprShader* _shader;
    int _currentFrame;

};

#endif  // _HL1SPRINSTANCE_H