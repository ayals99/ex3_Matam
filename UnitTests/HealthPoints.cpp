#include "HealthPoints.h"

int adjustHealth(int currentHealthPoints, int maxHealthPoints);

/** Arithmetic Operators implementation*/

/** Implementing + operator */
HealthPoints HealthPoints::operator+(int pointsToAdd){
    HealthPoints healthPointsResult = *this;
    healthPointsResult += pointsToAdd;
    return healthPointsResult;
}

HealthPoints operator+(const int pointsToAdd, const HealthPoints& healthPoints){
    HealthPoints healthPointsResult = healthPoints;
    healthPointsResult += pointsToAdd;
    return healthPointsResult;
}

/** Implementing += operator */
HealthPoints& HealthPoints::operator+=(const int valueToIncrease){
    m_currentHealth += valueToIncrease;
    m_currentHealth = adjustHealth(m_currentHealth, m_maxHealth);
    return *this;
}

/** Implementing - operator */

HealthPoints HealthPoints::operator-(const int pointsToSubtract){
    HealthPoints healthPointsResult = *this;
    healthPointsResult -= pointsToSubtract;
    return healthPointsResult;
}

/** Implementing -= operator */
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
    m_currentHealth = other.m_currentHealth;
    m_maxHealth = other.m_maxHealth;
    return *this;
}

HealthPoints& HealthPoints::operator=(const int healthToAssign){
    if(healthToAssign < MINIMAL_HEALTH){ // MINIMAL_HEALTH is a const int defined to zero in HealthPoints.h
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
bool HealthPoints::operator==(const int value) const {
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
bool HealthPoints::operator<(const int value) const{
    return (m_currentHealth < value);
}

/** Implementing > operator */
bool operator>(const int number, const HealthPoints& healthPoints){
    return (number > healthPoints.m_currentHealth);
}
bool HealthPoints::operator>(const HealthPoints& other) const{
    return (m_currentHealth > other.m_currentHealth);
}
bool HealthPoints::operator>(const int value) const{
    return (m_currentHealth > value);
}

/** Implementing <= operator */
bool HealthPoints::operator<=(const HealthPoints& other) const{
    return (m_currentHealth <= other.m_currentHealth);
}
bool operator<=(const int number, const HealthPoints& healthPoints){
    return (number <= healthPoints.m_currentHealth);
}
bool HealthPoints::operator<=(const int value) const{
    return (m_currentHealth <= value);
}

/** Implementing >= operator */
bool HealthPoints::operator>=(const HealthPoints& other) const{
    return (m_currentHealth >= other.m_currentHealth);
}
bool operator>=(const int number, const HealthPoints& other) {
    return (number >= other.m_currentHealth);
}
bool HealthPoints::operator>=(const int value) const{
    return (m_currentHealth >= value);
}

/** operator << implementation*/
std::ostream& operator<<(std::ostream& os, const HealthPoints& healthPoints){
    os << healthPoints.m_currentHealth << "(" << healthPoints.m_maxHealth << ")";
    return os;
}

/** adjustHealth() makes sure that m_currentHealth:
 * (1) doesn't exceed m_maxHealth
 * (2) doesn't go below zero
 * */
int adjustHealth(const int currentHealthPoints, const int maxHealthPoints){
    if(currentHealthPoints < MINIMAL_HEALTH){ // MINIMAL_HEALTH is a const int defined to zero in HealthPoints.h
        return MINIMAL_HEALTH;
    }
    else if(currentHealthPoints > maxHealthPoints){
        return maxHealthPoints;
    }
    else{
        return currentHealthPoints;
    }
}