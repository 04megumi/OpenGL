#include "Model.h"

Model::Model()
{

}
void Model::loadModel(std::string const& path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }
    processNode(scene->mRootNode, scene);
}
void Model::processNode(aiNode* node, const aiScene* scene)
{
    // 遍历并储存当前节点下所有的网格
    for (unsigned int i=0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    for (unsigned int i=0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}
Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    // 要填写到Mesh中的变量
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    
    // 遍历网格的所有顶点
    for (unsigned int i=0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector; //用于临时储存信息
        // 顶点位置
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;
        // 顶点法向量
        if(mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
        }
        // 将填好的顶点加入vertices中
        vertices.push_back(vertex);
    }
    
    
    // 遍历网格所有面片
    for (unsigned int i=0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j=0; j<face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    Mesh returnMesh;
    returnMesh.vertices = vertices;
    returnMesh.indices = indices;
    glGenVertexArrays(1, &returnMesh.VAO);
    glGenBuffers(1, &returnMesh.VBO);
    glGenBuffers(1, &returnMesh.EBO);
    glBindVertexArray(returnMesh.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, returnMesh.VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, returnMesh.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    glBindVertexArray(0);
    return returnMesh;
}
void Model::Draw()
{
    for (unsigned int i=0; i<meshes.size(); i++)
    {
        glBindVertexArray(meshes[i].VAO);
        glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(meshes[i].indices.size()), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}