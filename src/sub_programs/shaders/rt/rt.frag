#version 330 core

layout(std140) uniform ObjectData {
    mat4 modelMatrix;
    mat4 invModelMatrix;
    bool hasInverse;
    vec3 vertex;
    int meshType;
} objects[];

uniform uint objectCount;

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
    float t;
    vec3 normal;
    vec3 position;
    vec3 color;
    float reflectivity;
    float refractivity;
    float eta;
};

struct FunctionStackCell {
    int state;
    Ray ray;
    vec3 color;
    Intersection i;
    float intensity;
    float eta;
};

Intersection intersectSphere(Ray ray, vec3 center, float radius) {
    vec3 oc = ray.origin - center;
    float a = dot(ray.direction, ray.direction);
    float b = 2.0 * dot(oc, ray.direction);
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4.0 * a * c;
    float eta = 1.5;

    vec3 color;

    color = vec3(0.8, 0.6, 0.2);

    if (discriminant < 0.0) {
        return Intersection(0.0, vec3(0.0), vec3(0.0), vec3(0.0), 0.0, 0.0, 1.0);
    } else {
        int normsign = 1;
        float t = (-b - sqrt(discriminant)) / (2.0 * a);

        if (t < 0.0) {
            normsign = -1;
            t = (-b + sqrt(discriminant)) / (2.0 * a);
            eta = 1.0;
        }

        vec3 position = ray.origin + t * ray.direction;
        vec3 normal = normalize(position - center) * normsign;

        return Intersection(t, normal, position, color, 0.3, 0.3, eta);
    }
}

Intersection intersectPlane(Ray ray, vec3 normal, vec3 point) {
    float denom = dot(normal, ray.direction);

    if (abs(denom) > 1e-6) {
        float t = dot(point - ray.origin, normal) / denom;
        vec3 position = ray.origin + t * ray.direction;

        vec3 color;

        if (mod(floor(position.x) + floor(position.z), 2.0) == 0.0) {
            color = vec3(0.0, 0.0, 0.0);
        } else {
            color = vec3(1.0, 1.0, 1.0);
        }

        return Intersection(t, normal, position, color, 0.0, 0.0, 1.0);
    } else {
        return Intersection(0.0, vec3(0.0), vec3(0.0), vec3(0.0), 0.0, 0.0, 1.0);
    }
}

vec4 traceRay(Ray ray, int depth) {
    float treshold = 0.0001;
    float intensity = 1;

    vec3 rayColor = vec3(1.0, 1.0, 1.0);

    FunctionStackCell stack[8];
    int stackPointer = 0;
    int currentState = 0;
    int counter = 0;

    int meshTypes[] = int[](
        0,
        1,
        0,
        0,
        0,
        0,
        0,
        0,
        0
    );
    vec3 poses[] = vec3[](
        vec3(-0.75, -3.0, -5.0),
        vec3(0.0, -5.0, 0.0),
        vec3(0.75, -3.0, -5.0),
        vec3(0.0, -4.9, 1.0),
        vec3(1.0, -4.9, 0.0),
        vec3(0.0, -4.9, -1.0),
        vec3(-1.0, -4.9, 0.0),
        vec3(0.0, -5.9, 0.0),
        vec3(0.0, -3.9, 0.0)
    );

    vec4 color = vec4(0.0, 0.0, 0.0, 1.0);

    Intersection i;

    stack[stackPointer].state = 0;
    stack[stackPointer].ray = ray;
    stack[stackPointer].color = rayColor;
    stack[stackPointer].intensity = intensity;
    stack[stackPointer].i = i;
    stack[stackPointer].eta = 1.0;

    while (stackPointer >= 0) {
        counter++;
        ray = stack[stackPointer].ray;
        rayColor = stack[stackPointer].color;
        intensity = stack[stackPointer].intensity;
        i = stack[stackPointer].i;
        float eta = stack[stackPointer].eta;

        if (stack[stackPointer].state == 0) {
            i.t = -1.0;

            Intersection tmpI;

            for (int j = 0; j < 9; j++) {
                if (meshTypes[j] == 0) {
                    tmpI = intersectSphere(ray, poses[j], 0.5);
                } else if (meshTypes[j] == 1) {
                    tmpI = intersectPlane(ray, vec3(0.0, 1.0, 0.0), poses[j]);
                }
                if (tmpI.t > 0.0 && ((tmpI.t < i.t) || (i.t <= 0.0))) {
                    i = tmpI;
                }
            }

            if (i.t < 0.0) {
                color += vec4(0.2, 0.25, 0.5, 0.0) * intensity;

                stackPointer--;
                continue;
            }

            stack[stackPointer].state = 1;
            stack[stackPointer].i = i;

            vec3 lightDirection = normalize(vec3(0.0, -1.0, 0.0));

            Ray reflectedRay;
            reflectedRay.direction = -lightDirection;
            reflectedRay.origin = i.position + treshold * reflectedRay.direction;

            Intersection s;
            s.t = -1.0;

            for (int j = 0; j < 4; j++) {
                if (meshTypes[j] == 0) {
                    tmpI = intersectSphere(reflectedRay, poses[j], 0.5);
                } else if (meshTypes[j] == 1) {
                    tmpI = intersectPlane(reflectedRay, vec3(0.0, 1.0, 0.0), poses[j]);
                }
                if (tmpI.t > 0.0 && ((tmpI.t < s.t) || (s.t <= 0.0))) {
                    s = tmpI;
                }
            }

            if (s.t >= 0.0) {
                continue;
            }

            float diffuse = max(dot(i.normal, -lightDirection), 0.0);

            float specular = 0.0;

            if (diffuse > 0.0) {
                vec3 viewDirection = normalize(camera.position - i.position);
                vec3 halfwayDirection = normalize(-lightDirection + viewDirection);
                specular = pow(max(dot(i.normal, halfwayDirection), 0.0), 32.0);
            }

            color += vec4(
                diffuse * i.color +
                specular * vec3(1.0, 1.0, 1.0),
                0.0
            ) * intensity * (1 - i.reflectivity - i.refractivity);

            continue;
        }

        if (stackPointer >= depth - 1) {
            stackPointer--;

            continue;
        }

        if (stack[stackPointer].state == 1) {
            Ray reflectedRay;
            reflectedRay.direction = reflect(ray.direction, i.normal);
            reflectedRay.origin = i.position + treshold * reflectedRay.direction;

            stack[stackPointer].state = 2;

            stackPointer++;
            stack[stackPointer].state = 0;
            stack[stackPointer].ray = reflectedRay;
            stack[stackPointer].color = rayColor;
            stack[stackPointer].intensity = intensity * i.reflectivity;
            stack[stackPointer].eta = eta;

            continue;
        }

        if (stack[stackPointer].state == 2) {
            Ray refractionRay;
            refractionRay.direction = refract(ray.direction, i.normal, eta / i.eta);
            refractionRay.origin = i.position + treshold * refractionRay.direction;

            stack[stackPointer].state = 3;

            stackPointer++;

            stack[stackPointer].state = 0;
            stack[stackPointer].ray = refractionRay;
            stack[stackPointer].color = rayColor;
            stack[stackPointer].intensity = intensity * i.refractivity;
            stack[stackPointer].eta = i.eta;

            continue;
        }

        stackPointer--;
    }

    return color;
}

Ray MakeRay(float dx, float dy) {
    vec3 right = normalize(cross(camera.direction, camera.up));
    vec3 up = normalize(cross(right, camera.direction));

    float aspect = float(frame.width) / float(frame.height);

    // generate ray from camera
    Ray ray;
    ray.origin = camera.position;
    ray.direction = normalize(
        camera.direction +
        (2.0 * (gl_FragCoord.x + dx) / frame.width - 1.0) * right * aspect +
        (2.0 * (gl_FragCoord.y + dy) / frame.height - 1.0) * up
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
