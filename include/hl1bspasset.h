#ifndef _HL1BSPASSET_H_
#define	_HL1BSPASSET_H_

#include "hl1bsptypes.h"
#include "hl1wadasset.h"
#include "hl1shader.h"

#include <string>
#include <set>
#include <GL/glextl.h>

class Hl1BspAsset : public Hl1Asset
{
public:
    typedef struct sModel
    {
        glm::vec3 position;
        int firstFace;
        int faceCount;

        int rendermode;         // "Render Mode" [ 0: "Normal" 1: "Color" 2: "Texture" 3: "Glow" 4: "Solid" 5: "Additive" ]
        char renderamt;         // "FX Amount (1 - 255)"
        glm::vec4 rendercolor;  // "FX Color (R G B)"

    } tModel;

public:
    Hl1BspAsset(DataFileLocator& locator, DataFileLoader& loader);
    virtual ~Hl1BspAsset();

    virtual bool Load(const std::string &filename);

    void RenderFaces(const std::set<unsigned short>& visibleFaces);

    HL1::tBSPEntity* FindEntityByClassname(const std::string& classname);
    HL1::tBSPMipTexHeader* GetMiptex(int index);
    int FaceFlags(int index);

    // File format header
    HL1::tBSPHeader* _header;

    // These are mapped from the input file data
    Array<HL1::tBSPPlane> _planeData;
    Array<unsigned char> _textureData;
    Array<HL1::tBSPVertex> _verticesData;
    Array<HL1::tBSPNode> _nodeData;
    Array<HL1::tBSPTexInfo> _texinfoData;
    Array<HL1::tBSPFace> _faceData;
    Array<unsigned char> _lightingData;
    Array<HL1::tBSPClipNode> _clipnodeData;
    Array<HL1::tBSPLeaf> _leafData;
    Array<unsigned short> _marksurfaceData;
    Array<HL1::tBSPEdge> _edgeData;
    Array<int> _surfedgeData;
    Array<HL1::tBSPModel> _modelData;

    // These are parsed from the mapped data
    std::vector<HL1::tBSPEntity> _entities;
    std::vector<HL1::tBSPVisLeaf> _visLeafs;
    Array<tModel> _models;

private:
    // Constructs an Array from the given lump index. The memory in the lump is not owned by the lump
    template <typename T> bool LoadLump(const Array<byte>& filedata, Array<T>& lump, int lumpIndex)
    {
        HL1::tBSPLump& bspLump = this->_header->lumps[lumpIndex];
        if (filedata.count < (bspLump.offset + bspLump.size))
            return 0;

        lump.count = bspLump.size / sizeof(T);
        if (lump.count > 0)
            lump.data = (T*)(filedata.data + bspLump.offset);
        else
            lump.data = nullptr;

        return lump.count > 0;
    }

    void CalculateSurfaceExtents(const HL1::tBSPFace& in, float min[2], float max[2]) const;
    bool LoadLightmap(const HL1::tBSPFace& in, HlTexture& out, float min[2], float max[2]);

    bool LoadFacesWithLightmaps(std::vector<HL1::tFace>& faces, std::vector<HlTexture*>& lightmaps, std::vector<HL1::tVertex>& vertices);
    bool LoadTextures(std::vector<HlTexture*>& textures, const std::vector<Hl1WadAsset*>& wads);
    bool LoadModels();

    static std::vector<HL1::sBSPEntity> LoadEntities(const Array<byte>& entityData);
    static std::vector<HL1::tBSPVisLeaf> LoadVisLeafs(const Array<byte>& visdata, const Array<HL1::tBSPLeaf>& _leafData, const Array<HL1::tBSPModel>& _modelData);

};

#endif	/* _HL1BSPASSET_H_ */

