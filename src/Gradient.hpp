#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <vector>
#include <algorithm>

class ColorGradient {
public:
    void addStop(float distance, const glm::vec3& color) {
        stops.push_back({ distance, color });
        // Ensure the stops are sorted by distance
        std::sort(stops.begin(), stops.end(), [](const GradientStop& a, const GradientStop& b) {
            return a.distance < b.distance;
            });
    }

    glm::vec3 getColor(float distance) const {
        if (stops.empty()) return glm::vec3(1.0f); // Default to white if no stops exist

        // If the distance is below the first stop, return the first stop's color
        if (distance <= stops[0].distance)
            return stops[0].color;

        // Find the range the distance falls into
        for (size_t i = 1; i < stops.size(); ++i) {
            if (distance <= stops[i].distance) {
                // Interpolate between the two stops
                float t = (distance - stops[i - 1].distance) / (stops[i].distance - stops[i - 1].distance);
                t = sigmoid(t);
                return glm::mix(stops[i - 1].color, stops[i].color, t);
            }
        }

        // If the distance is beyond the last stop, return the last stop's color
        return stops.back().color;
    }

private:
    float sigmoid(float x, float b = 3) const {
        return 1.f / (1.f + std::pow(x/ (1-x), -b));
    }

    struct GradientStop {
        float distance;   // Distance from center
        glm::vec3 color;  // Color at this distance
    };
    std::vector<GradientStop> stops;
};