#version 330 core

uniform ObjectData {
    mat4 modelMatrix;
    mat4 invModelMatrix;
    bool hasInverse;
    vec3 vertex;
    int meshType;
} objects[10];

uniform int objectCount;

struct Camera {
    vec3 position;
    vec3 direction;
    vec3 up;
};

uniform Camera camera;

struct Frame {
    int width;
    int height;
};

uniform Frame frame;

out vec4 outColor;

struct Ray {
    vec3 origin;
    vec3 direction;
};

struct Intersection {
    float dist;
    vec3 normal;
    vec3 position;

    float shininess;
    vec3 ambientColor;
    vec3 diffuseColor;
    vec3 specularColor;
    float specularStrength;

    float reflectionStrength;
    float refractionStrength;

    float reflectionIndex;
};

struct FunctionStackCell {
    int state;
    Ray ray;
    vec3 color;
    Intersection i;
    float intensity;
    float eta;
};

float infinity = 1e10;
float epsilon = 1e-6;

Intersection intersectSphere(Ray ray, vec3 center, float radius) {
    vec3 oc = ray.origin - center;
    float a = dot(ray.direction, ray.direction);
    float b = 2.0 * dot(oc, ray.direction);
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4.0 * a * c;
    float eta = 1.33;

    vec3 color = vec3(0.8, 0.6, 0.2);

    if (discriminant < 0.0) {
        return Intersection(
            infinity,
            vec3(0.0), vec3(0.0),
            0.0,
            vec3(0.0), vec3(0.0), vec3(0.0), 0.0,
            0.0, 0.0,
            1.0
        );
    } else {
        float sqrt_discriminant = mySqrt(discriminant);
        float denom = 2.0 * a;
        float dist = (-b - sqrt_discriminant);
        int normsign = 1;

        if (dist < 0.0) {
            normsign = -1;
            dist += 2.0 * sqrt_discriminant;
            eta = 1.0;
        }

        dist /= denom;

        vec3 position = ray.origin + dist * ray.direction;
        vec3 normal = normalize(position - center) * normsign;

        return Intersection(
            dist, normal, position,
            32.0,
            vec3(0.0f, 0.05f, 0.05f), vec3(0.4f, 0.5f, 0.5f), vec3(0.4, 0.7, 0.7), 0.5,
            0.3, 0.3,
            eta
        );
    }
}

Intersection intersectPlane(Ray ray, vec3 point, vec3 normal) {
    float denom = dot(normal, ray.direction);

    if (abs(denom) < epsilon) {
        return Intersection(
            infinity, vec3(0.0), vec3(0.0),
            0.0,
            vec3(0.0), vec3(0.0), vec3(0.0), 0.0,
            0.0, 0.0,
            1.0
        );
    }

    float dist = dot(point - ray.origin, normal) / denom;
    vec3 position = ray.origin + dist * ray.direction;

    vec3 color;

    if (mod(floor(position.x) + floor(position.z), 2.0) == 0.0) {
        color = vec3(0.0, 0.0, 0.0);
    } else {
        color = vec3(1.0, 1.0, 1.0);
    }

    return Intersection(
        dist, normal, position,
        32.0,
        vec3(0.0f, 0.1f, 0.06f), vec3(0.0f, 0.51f, 0.51f), vec3(0.5, 0.5, 0.5), 0.5,
        0.3, 0.3,
        1.0
    );
}

Intersection intersectTriangle(Ray ray, vec3 v0, vec3 v1, vec3 v2) {
    vec3 e1 = v1 - v0;
    vec3 e2 = v2 - v0;
    vec3 pvec = cross(ray.direction, e2);
    float det = dot(e1, pvec);

    if (abs(det) < epsilon) {
        return Intersection(
            infinity, vec3(0.0), vec3(0.0),
            0.0,
            vec3(0.0), vec3(0.0), vec3(0.0), 0.0,
            0.0, 0.0,
            1.0
        );
    }

    float inv_det = 1.0 / det;
    vec3 tvec = ray.origin - v0;
    float u = dot(tvec, pvec) * inv_det;

    if (u < 0.0 || u > 1.0) {
        return Intersection(
            infinity, vec3(0.0), vec3(0.0),
            0.0,
            vec3(0.0), vec3(0.0), vec3(0.0), 0.0,
            0.0, 0.0,
            1.0
        );
    }

    vec3 qvec = cross(tvec, e1);
    float v = dot(ray.direction, qvec) * inv_det;

    if (v < 0.0 || u + v > 1.0) {
        return Intersection(
            infinity, vec3(0.0), vec3(0.0),
            0.0,
            vec3(0.0), vec3(0.0), vec3(0.0), 0.0,
            0.0, 0.0,
            1.0
        );
    }

    float dist = dot(e2, qvec) * inv_det;

    vec3 position = ray.origin + dist * ray.direction;
    vec3 normal = normalize(cross(e1, e2));

    return Intersection(
        dist, normal, position,
        32.0,
        vec3(0.0f, 0.05f, 0.05f), vec3(0.4f, 0.5f, 0.5f), vec3(0.4, 0.7, 0.7), 0.5,
        0.3, 0.3,
        1.0
    );
}

Intersection intersectCube(Ray ray, vec3 center, float size) {
    vec3 halfSize = vec3(size / 2.0, size / 2.0, size / 2.0);
    vec3 min = center - halfSize;
    vec3 max = center + halfSize;

    float tmin = (min.x - ray.origin.x) / ray.direction.x;
    float tmax = (max.x - ray.origin.x) / ray.direction.x;

    vec3 normal;
    vec3 position;

    if (tmin > tmax) {
        float temp = tmin;
        tmin = tmax;
        tmax = temp;
    }

    float tymin = (min.y - ray.origin.y) / ray.direction.y;
    float tymax = (max.y - ray.origin.y) / ray.direction.y;

    if (tymin > tymax) {
        float temp = tymin;
        tymin = tymax;
        tymax = temp;
    }

    if ((tmin > tymax) || (tymin > tmax)) {
        return Intersection(
            infinity, vec3(0.0), vec3(0.0),
            0.0,
            vec3(0.0), vec3(0.0), vec3(0.0), 0.0,
            0.0, 0.0,
            1.0
        );
    }

    if (tymin > tmin) {
        tmin = tymin;
    }

    if (tymax < tmax) {
        tmax = tymax;
    }

    float tzmin = (min.z - ray.origin.z) / ray.direction.z;
    float tzmax = (max.z - ray.origin.z) / ray.direction.z;

    if (tzmin > tzmax) {
        float temp = tzmin;
        tzmin = tzmax;
        tzmax = temp;
    }

    if ((tmin > tzmax) || (tzmin > tmax)) {
        return Intersection(
            infinity, vec3(0.0), vec3(0.0),
            0.0,
            vec3(0.0), vec3(0.0), vec3(0.0), 0.0,
            0.0, 0.0,
            1.0
        );
    }

    if (tzmin > tmin) {
        tmin = tzmin;
    }

    if (tzmax < tmax) {
        tmax = tzmax;
    }

    if (tmin < 0.0) {
        tmin = tmax;
        if (tmin < 0.0) {
            return Intersection(
                infinity, vec3(0.0), vec3(0.0),
                0.0,
                vec3(0.0), vec3(0.0), vec3(0.0), 0.0,
                0.0, 0.0,
                1.0
            );
        }
    }

    position = ray.origin + tmin * ray.direction;
    normal = vec3(0.0, 0.0, 0.0);

    if (abs(position.x - min.x) < 0.0001) {
        normal.x = -1.0;
    } else if (abs(position.x - max.x) < 0.0001) {
        normal.x = 1.0;
    } else if (abs(position.y - min.y) < 0.0001) {
        normal.y = -1.0;
    } else if (abs(position.y - max.y) < 0.0001) {
        normal.y = 1.0;
    } else if (abs(position.z - min.z) < 0.0001) {
        normal.z = -1.0;
    } else if (abs(position.z - max.z) < 0.0001) {
        normal.z = 1.0;
    }

    if (dot(normal, ray.direction) > 0.0) {
        normal = -normal;
    }

    return Intersection(
        tmin, normal, position,
        32.0,
        vec3(0.1745f, 0.01175f, 0.01175f), vec3(0.61424f, 0.04136f, 0.04136f), vec3(0.727811f, 0.626959f, 0.626959f), 0.5,
        0.1, 0.1,
        1.0
    );
}

Intersection findIntersection(Ray ray) {
    int meshTypes[] = int[](
        2,
        1,
        3
    );
    vec3 poses[] = vec3[](
        vec3(-0.75, -0.0, -5.0),
        vec3(0.0, -1.0, -5.0),
        vec3(0.75, -0.0, -5.0)
    );
    int objectsCount = 0;

    Intersection currentIntersection;
    Intersection closestIntersection;
    closestIntersection.dist = infinity;

    return closestIntersection;

    for (int i = 0; i < objectsCount; i++) {
        if (meshTypes[i] == 1) {
            currentIntersection = intersectPlane(ray, poses[i], vec3(0.0, 1.0, 0.0));
        } else if (meshTypes[i] == 2) {
            currentIntersection = intersectSphere(ray, poses[i], 0.5);
        } else if (meshTypes[i] == 3) {
            currentIntersection = intersectCube(ray, poses[i], 1.0);
        }

        if (currentIntersection.dist < closestIntersection.dist) {
            closestIntersection = currentIntersection;
        }
    }

    return closestIntersection;
}

vec3 findSurfaceColor(Intersection i, Ray ray, float intensity) {
    vec3 color = vec3(0.0, 0.0, 0.0);

    vec3 lightPos = vec3(0.0, 1.0, 0.0);
    vec3 lightColor = vec3(1.0, 1.0, 1.0);

    vec3 lightDir = normalize(lightPos - i.position);
    vec3 viewDir = normalize(ray.origin - i.position);
    vec3 reflectDir = reflect(-lightDir, i.normal);

    float diffuse = max(dot(i.normal, lightDir), 0.0);
    float specular = pow(max(dot(viewDir, reflectDir), 0.0), i.shininess);

    color += i.ambientColor;
    color += diffuse * i.diffuseColor;
    color += specular * lightColor * i.specularColor;

    color *= intensity;
    color *= (1 - i.reflectionStrength - i.refractionStrength);

    return color;
}

vec4 traceRay(Ray ray, int depth) {
    float treshold = 0.0001;
    float intensity = 1;

    vec3 rayColor = vec3(1.0, 1.0, 1.0);

    FunctionStackCell stack[8];
    int stackPointer = 0;
    int currentState = 0;

    vec4 color = vec4(0.0, 0.0, 0.0, 1.0);

    Intersection i;

    stack[stackPointer].state = 0;
    stack[stackPointer].ray = ray;
    stack[stackPointer].color = rayColor;
    stack[stackPointer].intensity = intensity;
    stack[stackPointer].i = i;
    stack[stackPointer].eta = 1.0;

    while (stackPointer >= 0) {
        if (stackPointer >= depth - 1) {
            stackPointer--;

            continue;
        }

        ray = stack[stackPointer].ray;
        rayColor = stack[stackPointer].color;
        intensity = stack[stackPointer].intensity;
        i = stack[stackPointer].i;
        float eta = stack[stackPointer].eta;

        stack[stackPointer].state++;

        if (stack[stackPointer].state == 0) {
            i = findIntersection(ray);

            if (i.dist == infinity || intensity < 0.01) {
                color += vec4(0.2, 0.25, 0.5, 0.0) * intensity;

                stackPointer--;
                continue;
            }

            stack[stackPointer].state = 5;
            stack[stackPointer].i = i;

            color += vec4(findSurfaceColor(i, ray, intensity), 0.0);
        } else if (stack[stackPointer].state == 1) {
            Ray reflectedRay;
            reflectedRay.direction = reflect(ray.direction, i.normal);
            reflectedRay.origin = i.position + treshold * reflectedRay.direction;

            stackPointer++;

            stack[stackPointer].state = 0;
            stack[stackPointer].ray = reflectedRay;
            stack[stackPointer].color = rayColor;
            stack[stackPointer].intensity = intensity * i.reflectionStrength;
            stack[stackPointer].eta = eta;
        } else if (stack[stackPointer].state == 2) {
            Ray refractionRay;
            refractionRay.direction = refract(ray.direction, i.normal, eta / i.reflectionIndex);
            refractionRay.origin = i.position + treshold * refractionRay.direction;

            stackPointer++;

            stack[stackPointer].state = 0;
            stack[stackPointer].ray = refractionRay;
            stack[stackPointer].color = rayColor;
            stack[stackPointer].intensity = intensity * i.refractionStrength;
            stack[stackPointer].eta = i.reflectionIndex;
        } else if (stack[stackPointer].state >= 3) {
            stackPointer--;
        }
    }

    return color;
}

Ray MakeRay(float dx, float dy) {
    vec3 right = normalize(cross(camera.direction, camera.up));
    vec3 up = normalize(cross(right, camera.direction));

    float aspect = float(frame.width) / float(frame.height);
    float fov = 70.0f;
    float half_tan_fov = tan(fov * 0.5 * 3.141592 / 180.0);

    // generate ray from camera
    Ray ray;
    ray.origin = camera.position;
    ray.direction = normalize(
        camera.direction +
        (2.0 * (gl_FragCoord.x + dx) / frame.width - 1.0) * right * aspect * half_tan_fov +
        (2.0 * (gl_FragCoord.y + dy) / frame.height - 1.0) * up * half_tan_fov
    );

    return ray;
}

void main() {
    int depth = 8;
    int samling = 3;

    vec4 color = vec4(0.0, 0.0, 0.0, 0.0);

    for (int i = 0; i < samling; i++) {
        for (int j = 0; j < samling; j++) {
            Ray ray = MakeRay(float(i) / float(samling), float(j) / float(samling));
            color += traceRay(ray, depth);
        }
    }

    color /= float(samling * samling);

    outColor = clamp(color, 0.0, 1.0);
}
