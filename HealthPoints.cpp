#include "HealthPoints.h"
#include <cassert>

int adjustHealth(int currentHealthPoints, int maxHealthPoints);

/** Arithmetic Operators implementation*/

/** Implementing + operator */
//HealthPoints& HealthPoints::operator+(const HealthPoints& other) {
//    m_currentHealth += other.m_currentHealth;
//    m_currentHealth = adjustHealth(m_currentHealth, m_maxHealth);
//    return *this;
//}

HealthPoints& HealthPoints::operator+(int pointsToAdd){
    m_currentHealth += pointsToAdd;
    m_currentHealth = adjustHealth(m_currentHealth, m_maxHealth);
    return *this;
}

HealthPoints& operator+(int pointsToAdd, HealthPoints& healthPoints){
    healthPoints += pointsToAdd;
    return healthPoints;
}

/** Implementing += operator */
//HealthPoints& HealthPoints::operator+=(HealthPoints& other){
//    m_currentHealth += other.m_currentHealth;
//    m_currentHealth = adjustHealth(m_currentHealth, m_maxHealth);
//    return *this;
//}
HealthPoints& HealthPoints::operator+=(int valueToIncrease){
    m_currentHealth += valueToIncrease;
    m_currentHealth = adjustHealth(m_currentHealth, m_maxHealth);
    return *this;
}

/** Implementing - operator */
//HealthPoints& HealthPoints::operator-(const HealthPoints& other){
//    m_currentHealth -= other.m_currentHealth;
//    m_currentHealth = adjustHealth(m_currentHealth, m_maxHealth);
//    return *this;
//}
HealthPoints& HealthPoints::operator-(const int pointsToSubtract){
    m_currentHealth -= pointsToSubtract;
    m_currentHealth = adjustHealth(m_currentHealth, m_maxHealth);
    return *this;
}

/** Implementing -= operator */
//HealthPoints& HealthPoints::operator-=(HealthPoints& other){
//    m_currentHealth -= other.m_currentHealth;
//    m_currentHealth = adjustHealth(m_currentHealth, m_maxHealth);
//    return *this;
//}
HealthPoints& HealthPoints::operator-=(const int valueToDecrease){
    m_currentHealth -= valueToDecrease;
    m_currentHealth = adjustHealth(m_currentHealth, m_maxHealth);
    return *this;
}

/** Assignment Operators implementation*/
HealthPoints& HealthPoints::operator=(const HealthPoints& other) {
    if(&other == this){
        return *this;
    }
    assert(other.m_maxHealth >= MINIMAL_HEALTH);
    assert(other.m_currentHealth >= MINIMAL_HEALTH);

    m_currentHealth = other.m_currentHealth;
    m_maxHealth = other.m_maxHealth;
    return *this;
}
HealthPoints& HealthPoints::operator=(const int healthToAssign){
    if(healthToAssign < 0){
        throw HealthPoints::InvalidArgument();
    }
    m_currentHealth = healthToAssign;
    m_maxHealth = healthToAssign;
    return *this;
}

/** Boolean Operators implementation*/

/** Implementing == operator */
bool HealthPoints::operator==(const HealthPoints& other) const{
    return (m_currentHealth == other.m_currentHealth);
}
bool HealthPoints::operator==(int value) const {
    return (m_currentHealth == value);
}
bool operator==(const int value, const HealthPoints& healthPoints){
    return (value == healthPoints.m_currentHealth);
}

/** Implementing != operator */
bool HealthPoints::operator!=(const HealthPoints& other) const{
    return (m_currentHealth != other.m_currentHealth);
}
bool HealthPoints::operator!=(int value) const {
    return (m_currentHealth != value);
}
bool operator!=(const int value, const HealthPoints& healthPoints){
    return (value != healthPoints.m_currentHealth);
}

/** Implementing < operator */
bool operator<(const int number, const HealthPoints& healthPoints){
    return (number < healthPoints.m_currentHealth);
}
bool HealthPoints::operator<(const HealthPoints& other) const{
    return (m_currentHealth < other.m_currentHealth);
}

/** Implementing > operator */
bool operator>(const int number, const HealthPoints& healthPoints){
    return (number > healthPoints.m_currentHealth);
}
bool HealthPoints::operator>(const HealthPoints& other) const{
    return (m_currentHealth > other.m_currentHealth);
}

/** Implementing <= operator */
bool HealthPoints::operator<=(const HealthPoints& other) const{
    return (m_currentHealth <= other.m_currentHealth);
}
bool operator<=(const int number, const HealthPoints& healthPoints){
    return (number <= healthPoints.m_currentHealth);
}

/** Implementing >= operator */
bool HealthPoints::operator>=(const HealthPoints& other) const{
    return (m_currentHealth >= other.m_currentHealth);
}
bool operator>=(int number, const HealthPoints& other) {
    return (number >= other.m_currentHealth);
}

/** std::cout operator implementation*/
std::ostream& operator<<(std::ostream& os, const HealthPoints& healthPoints){
    os << healthPoints.m_currentHealth << "(" << healthPoints.m_maxHealth << ")";
    return os;
}

int adjustHealth(int currentHealthPoints, int maxHealthPoints){
    if(currentHealthPoints < MINIMAL_HEALTH){
        return MINIMAL_HEALTH;
    }
    else if(currentHealthPoints > maxHealthPoints){
        return maxHealthPoints;
    }
    else{
        return currentHealthPoints;
    }
}