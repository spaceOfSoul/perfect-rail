#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class AudioVisualizer {
    int frequencyFrame;
    int amplitudeFrame;

    std::vector<sf::RectangleShape> freqRangeRects;
    std::vector<double> amplitudeVisualizationVector;
    std::vector<sf::CircleShape> amplitudeParticles;

    sf::RectangleShape backgroundRect;

public:
    AudioVisualizer();
    std::vector<sf::RectangleShape>& getFreqRangeRects();
    sf::RectangleShape& getBackgroundRect();
    std::vector<sf::CircleShape>& getAmplitudeParticles();
    void setAmplitudeVisualizationVector(std::vector<double> amplitudeVisualizationVector);
    void update(std::vector< std::vector <double> >& frequencyVisualizationVector, double songPlayingOffset);
};
