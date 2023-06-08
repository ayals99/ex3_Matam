#ifndef HEALTH_POINTS_H
#define HEALTH_POINTS_H

#include <iostream>
const int MINIMAL_HEALTH = 0;
const int DEFAULT_MAXIMAL_HEALTH = 100;

class HealthPoints {

private:
    int m_maxHealth;
    int m_currentHealth;

public:
    class InvalidArgument{};

    /** Constructor*/
    /** @description Construct a new Health Points object
     *
     * @param maxHealth or no input
     *
     * @assumption maxHealth > 0
     * @throw InvalidHealth otherwise
     *
     * @return HealthPoints object with maxHealth
     */
    HealthPoints(int maxHealth = DEFAULT_MAXIMAL_HEALTH) : m_maxHealth(maxHealth), m_currentHealth(maxHealth) {
        if (maxHealth <= MINIMAL_HEALTH) {
            throw InvalidArgument();
        }
    }

    /** copy constructor */
    HealthPoints(const HealthPoints& other){
        m_maxHealth = other.m_maxHealth;
        m_currentHealth = other.m_currentHealth;
    }

    /**
     * @description Destroy the Health Points object
     *
     */
    ~HealthPoints() = default;

    /** Arithmetic Operators Declarations*/

    /** Declaring + operator */
    HealthPoints operator+(int pointsToAdd);

    /** Declaring += operator */
    HealthPoints& operator+=(int valueToIncrease);

    /** Declaring - operator */
    HealthPoints operator-(int pointsToSubtract);

    /** Declaring -= operator */
    HealthPoints& operator-=(int valueToDecrease);

    /** Assignment Operators Declaration*/
    HealthPoints& operator=(const HealthPoints& other);
    HealthPoints& operator=(int healthToAssign);

    /** Boolean Operators Declarations*/

    /** Declaring == operator */
    bool operator==(const HealthPoints& other) const;
    bool operator==(int value) const;
    friend bool operator==(int value, const HealthPoints& healthPoints);

    /** Declaring != operator */
    bool operator!=(const HealthPoints& other) const;
    bool operator!=(int value) const;
    friend bool operator!=(int value, const HealthPoints& healthPoints);

    /** Declaring < operator */
    bool operator<(const HealthPoints& other) const;
    friend bool operator<(int number, const HealthPoints& healthPoints);

    /** Declaring > operator */
    bool operator>(const HealthPoints& other) const;
    friend bool operator>(int number, const HealthPoints& healthPoints);

    /** Declaring <= operator */
    bool operator<=(const HealthPoints& other) const;
    friend bool operator<=(int number, const HealthPoints& healthPoints);

    /** Declaring >= operator */
    bool operator>=(const HealthPoints& other) const;
    friend bool operator>=(int number, const HealthPoints& other);

    /** Friending << operator */
    friend std::ostream& operator<<(std::ostream& os, const HealthPoints& healthPoints);
};

HealthPoints operator+(int pointsToSub, HealthPoints& healthPoints);

bool operator==(int value, const HealthPoints& healthPoints);

bool operator!=(int,const HealthPoints&);

bool operator<(int, const HealthPoints&);

bool operator<=(int, const HealthPoints&);

bool operator>(int, const HealthPoints&);

bool operator>=(int, const HealthPoints&);

std::ostream &operator<<(std::ostream& os, const HealthPoints& healthPoints);

#endif