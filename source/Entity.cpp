#include "Entity.h"

void Entity::printInfo() {
    cout << "I have " << this->numIndices << " indices" << endl;
    cout << "my color is (rgba) " <<
      this->color[0] << ", " <<
        this->color[1] << ", " <<
          this->color[2] << ", " <<
            this->color[3] << endl;

    if (this->wireframe) {
        cout << "I am wireframed" << endl;
    } else {
        cout << "No wireframe for me" << endl;
    }

    if (this->fill) {
        cout << "I am filled" << endl;
    } else {
        cout << "No fill for me" << endl;
    }

    cout << "position" << endl;
    this->position->printInfo();

    cout << "mvpLoc is " << this->mvpLoc << endl;
    cout << "colorLoc is " << this->colorLoc << endl;
    cout << "angle is " << this->angle << endl;
}

void Entity::update(float deltatime, vector<char *> input) {
}

void Entity::setCollection(vector<Entity *> *entityCollection) {
    this->entityCollection = entityCollection;
}

string Entity::getName() {
    assertS(this->name != "", "Unnamed entity");
    return this->name;
}

string Entity::getType() {
    assertS(this->type != "", "Untyped entity");
    return this->type;
}

void Entity::render() {
    ESMatrix modelview = mvpMatrix;
    // zet de posities
    esTranslate(&modelview, this->position->x, this->position->y, this->position->z);
    // gebruik de ingeladen shader
    glUseProgram(this->programObject);
    // 3x doe iets belangrijks
    glVertexAttribPointer    (this->positionLoc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), this->vertices);
    glEnableVertexAttribArray(this->positionLoc);
    glUniformMatrix4fv       (this->mvpLoc,      1, GL_FALSE, (GLfloat *) &modelview);
    glUniform4fv             (this->colorLoc,    1, this->color);
    if (this->wireframe) {
        glDrawElements(GL_LINES, this->numIndices, GL_UNSIGNED_BYTE, this->indices);
    }
    if (this->fill) {
        glDrawElements(GL_TRIANGLES, this->numIndices, GL_UNSIGNED_BYTE, this->indices);
    }
}

void Entity::loadShaders() {
  this->programObject = esLoadProgram(*defaultVertexShader, *defaultFragmentShader);

  assertS(this->programObject != 0, "program object is wrong, that means something went wrong...");

  this->positionLoc   = glGetAttribLocation (this->programObject, "a_position");
  this->mvpLoc        = glGetUniformLocation(this->programObject, "u_mvpMatrix");
  this->colorLoc      = glGetUniformLocation(this->programObject, "color");

  assertS(this->positionLoc != -1, "positionLocation is -1, bad stuff :(");
  assertS(this->mvpLoc      != -1, "mvpLocation is -1, bad stuff :(");
  assertS(this->colorLoc    != -1, "colorLocation is -1, bad stuff :(");
}

Entity* Entity::findEntity(string name, string type) {
    for (unsigned int i = 0; i < this->entityCollection->size(); i += 1) {
        Entity *entity = (* this->entityCollection)[i];
        if (entity->name == name && entity->type == type) {
            return entity;
        }
    }

    assertS(false, "No entity found... this shouldn't happen!");
}

Entity::Entity() {
  cout << "constructing an entity" << endl;
  this->position = new Vector();
}
