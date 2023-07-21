#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1080, 600), "Perfect Rail!", sf::Style::Close);

    bool fullscreen = true;

    // �簢�� �װ��� ������ �׸�
    sf::RectangleShape line1(sf::Vector2f(10.f, 600.f));
    sf::RectangleShape line2(sf::Vector2f(10.f, 600.f));
    sf::RectangleShape line3(sf::Vector2f(10.f, 600.f));
    sf::RectangleShape line4(sf::Vector2f(10.f, 600.f));

    // �簢������ ��ġ ����
    line1.setPosition(100.f, 0.f);
    line2.setPosition(300.f, 0.f);
    line3.setPosition(500.f, 0.f);
    line4.setPosition(700.f, 0.f);

    // ���� ����
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            // F5 Ű�� ���ȴ��� Ȯ��
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5)
            {
                fullscreen = !fullscreen;
                window.create(fullscreen ? sf::VideoMode::getDesktopMode() : sf::VideoMode(1080, 600),
                    "Perfect Rail!",
                    fullscreen ? sf::Style::Fullscreen : sf::Style::Close);
            }
        }

        // ȭ�� Ŭ����
        window.clear();

        // ���ε� ������
        window.draw(line1);
        window.draw(line2);
        window.draw(line3);
        window.draw(line4);

        // ȭ�� ������Ʈ
        window.display();
    }

    return 0;
}
