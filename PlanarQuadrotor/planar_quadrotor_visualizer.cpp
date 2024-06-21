#include "planar_quadrotor_visualizer.h"

PlanarQuadrotorVisualizer::PlanarQuadrotorVisualizer(PlanarQuadrotor *quadrotor_ptr): quadrotor_ptr(quadrotor_ptr) {}

/**
 * TODO: Improve visualizetion
 * 1. Transform coordinates from quadrotor frame to image frame so the circle is in the middle of the screen
 * 2. Use more shapes to represent quadrotor (e.x. try replicate http://underactuated.mit.edu/acrobot.html#section3 or do something prettier)
 * 3. Animate proppelers
 */
void PlanarQuadrotorVisualizer::render(std::shared_ptr<SDL_Renderer> &gRenderer) {
    Eigen::VectorXf state = quadrotor_ptr->GetState();
    float q_x, q_y, q_theta;

    /* x, y, theta coordinates */
    q_x = 640 + state[0];
    q_y = 360 + state[1];
    q_theta = state[2];

    SDL_SetRenderDrawColor(gRenderer.get(), 0xFF, 0x00, 0x00, 0xFF);
    filledCircleColor(gRenderer.get(), q_x, q_y, 30, 0xFF0000FF);

    float arm_length = 50.0f;
    float R = 15.0f;

    float arm_x1 = q_x + arm_length * cos(q_theta);
    float arm_y1 = q_y + arm_length * sin(q_theta);
    float arm_x2 = q_x - arm_length * cos(q_theta);
    float arm_y2 = q_y - arm_length * sin(q_theta);

    filledCircleColor(gRenderer.get(), arm_x1, arm_y1, R, 0x6082B6FF);
    filledCircleColor(gRenderer.get(), arm_x2, arm_y2, R, 0x6082B6FF);

    SDL_SetRenderDrawColor(gRenderer.get(), 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderDrawLine(gRenderer.get(), q_x, q_y, arm_x1, arm_y1);
    SDL_RenderDrawLine(gRenderer.get(), q_x, q_y, arm_x2, arm_y2);
    
    static float angle = 0.0f;
    angle += 0.1f;

    float R_x1 = arm_x1 + R * cos(angle);
    float R_y1 = arm_y1 + R * sin(angle);
    float R_x2 = arm_x2 + R * cos(angle);
    float R_y2 = arm_y2 + R * sin(angle);

    SDL_SetRenderDrawColor(gRenderer.get(), 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderDrawLine(gRenderer.get(), arm_x1, arm_y1, R_x1, R_y1);
    SDL_RenderDrawLine(gRenderer.get(), arm_x2, arm_y2, R_x2, R_y2);
}