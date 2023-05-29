#IFNDEF HEALTHPOINTS_H
#DEFINE HEALTHPOINTS_H

const int MINIMAL_HEALTH = 0;


class HealthPoints {
    class InvalidHealth {};
    private:
        int m_maxHealth;
        int m_currentHealth;
    public:

    /** Constructor*/
    /** @description Construct a new Health Points object
     *
     * @param health
     */
    HealthPoints(int maxHealth = 100) : m_maxHealth(maxHealth), m_currentHealth(maxHealth) {
        if(maxHealth <= 0){
            throw HealthPoints::InvalidHealth;
        }
    }

    /** copy constructor */
    HealthPoints(const HealthPoints& other) : m_maxHealth(other.m_maxHealth), m_currentHealth(other.m_currentHealth) {}

    /**
     * @description Destroy the Health Points object
     *
     */
    ~HealthPoints() = default;

    /** Arithmetic Operators */
    HealthPoints& operator+(const HealthPoints& other){
        this->m_currentHealth += other.m_currentHealth;
        return *this;
    }

    HealthPoints& operator+(int pointsToAdd){
        this->m_currentHealth += pointsToAdd;
        return *this;
    }

    HealthPoints& operator-(int pointsToSub){
        this->m_currentHealth -= pointsToSub;
        return *this;
    }

    HealthPoints& operator+=(HealthPoints& other){
        m_currentHealth += other.m_currentHealth;
        return *this;
    }

    HealthPoints& operator-=(HealthPoints& other){
        m_currentHealth -= other.m_currentHealth;
        return *this;
    }

    HealthPoints& operator=(const int healthToAssign){
        m_currentHealth = healthToAssign;
        return *this;
    }

    /** Boolean Operators */
    bool operator==(const HealthPoints& other) const {
        return m_currentHealth == other.m_currentHealth;
    }

    bool operator!=(const HealthPoints& other) const {
        return (m_currentHealth != other.m_currentHealth);
    }

    bool operator<(const HealthPoints& other) const {
        return (m_currentHealth < other.m_currentHealth);
    }

    bool operator>(const HealthPoints& other) const {
        return (m_currentHealth > other.m_currentHealth);
    }

    /**std::cout operetors*/
    friend std::ostream& operator<<(std::ostream& os, const HealthPoints& healthPoints) {
        os << healthPoints.m_currentHealth << "(" << healthPoints.m_maxHealth << ")";
        return os;
    }

    /**Getters and setters for health points*/
    int getHealth() const {
        return m_currentHealth;
    }

    void setHealth(int health){
        this->m_currentHealth = health;
    }

    void addHealth(int healthToAdd){
        this->m_currentHealth += healthToAdd;
    }

    void subtractHealth(int healthToSubtract){
        this->m_currentHealth -= healthToSubtract;
    }

    bool isAlive() const {
        return (m_currentHealth > 0);
    }
}

#ENDIF