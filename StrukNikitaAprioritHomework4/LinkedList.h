#pragma once
#include <initializer_list>
#include <functional>
#include <memory>

template <typename T>
class LinkedList
{
private:
	/**
	 * \brief Структура Node для зберігання даних та наступного покажчика
	 * (Node structure for holding data and next node pointer)
	 */
	struct Node
	{
		T data;
		std::unique_ptr<Node> nextNode;
		Node(const T& value) : data(value), nextNode(nullptr)
		{
		}
	};

	/**
	 * \brief Вказівник Head на перший показчик та змінна size для зберігання розміру списку.
	 * (The Head pointer to the first indicator and the size variable to store the size of the list)
	 */
	std::unique_ptr<Node> head;
	size_t listSize;
public:
	/**
	 *
	 * \brief Конструктор за замовчуванням
	 * (Default Constructor)
	 */
	LinkedList() : head(nullptr), listSize(0)
	{
	}

	/** Конструктор списку ініціалізаторів
	 * \brief
	 * (Initializer List Constructor)
	 * \param initializerList - список ініціалізаторів (an initializer list).
	 */
	LinkedList(const std::initializer_list<T>& initializerList) : LinkedList()
	{
		for(const auto& item: initializerList)
		{
			push_front(item);
		}
	}

	/**
	 * \brief Конструктор копіювання.
	 * (Copy Constructor)
	 * \param other - інший список (another list).
	 */
	LinkedList(const LinkedList& other) : LinkedList()
	{
        for (auto it = other.begin(); it != other.end(); ++it)
            push_front(*it);
    }

	/**
	 * \brief Конструктор переміщення
	 * (Move Constructor)
	 * \param other - інший список (another list).
	 */
	LinkedList(LinkedList&& other) noexcept : head(std::move(other.head)), listSize(other.listSize)
	{
        other.listSize = 0;
    }

	/**
	 * \brief Оператор присвоєння копії
	 * (Copy Assignment Operator)
	 * \param other - інший список (another list).
	 * \return 
	 */
	LinkedList& operator=(const LinkedList& other)
	{
        if (this != &other)
        {
            LinkedList temp(other);
            swap(temp);
        }
        return *this;
    }

	/**
	 * \brief Оператор присвоєння переміщення
	 * (Move Assignment Operator)
	 * \param other - інший список (another list).
	 * \return 
	 */
	LinkedList& operator=(LinkedList&& other) noexcept
	{
        if (this != &other)
        {
            head = std::move(other.head);
            listSize = other.listSize;
            other.listSize = 0;
        }
        return *this;
    }

	/**
	 * \brief Метод вставки елемента на початок списку
	 * (Method to insert item at the beginning of the list)
	 * \param value - елемент, який буде додано до списку
	 */
	void push_front(const T& value)
	{
        std::unique_ptr<Node> newNode = std::make_unique<Node>(value);
        newNode->nextNode = std::move(head);
        head = std::move(newNode);
        ++listSize;
    }

	/**
	 * \brief Метод отримання розміру списку 
	 * (Method to get the size of the list)
	 */
	size_t getSize() const
	{
        return listSize;
    }

	/**
	 * \brief Метод видалення першого елемента зі списку
	 * (Method to remove the first item from the list).
	 */
	void pop_front()
	{
        if (head) 
        {
            head = std::move(head->nextNode);
            --listSize;
        }
    }

	/**
	 * \brief Метод для перевірки, чи список порожній
	 * (Method to check if the list is empty) 
	 */
	bool empty() const
	{
        return listSize == 0;
    }
    /* Клас Iterator для ітерації над списком 
     * (Iterator class to iterate over the list).
     */
    class Iterator
	{
    private:
        Node* currentNode;
    public:
        Iterator(Node* node) : currentNode(node) {}

        /**
         * \brief Оператор розіменування для отримання даних у currentNode
         *  (Dereference operator to get the data at current node)
         */
        T& operator*() const
		{
            return currentNode->data;
        }

        /**
         * \brief Оператор інкременту для переходу до наступного вузла
         * (Increment operator to move to the next node)
         */
        Iterator& operator++()
		{
            currentNode = currentNode->nextNode.get();
            return *this;
        }

        /**
         * \brief Оператор нерівності для порівняння ітераторів
         * (Inequality operator to compare iterators)
         * \param other - інший ітератор.
         */
        bool operator!=(const Iterator& other) const
		{
            return currentNode != other.currentNode;
        }
    };

	/**
	 * \brief Метод отримання ітератора, що вказує на початок списку
	 *  Method to get iterator pointing to the beginning of the list
	 */
	Iterator begin() const
    {
	    return Iterator(head.get());
    }

	/**
	 * \brief Метод отримання ітератора, що вказує на кінець списку
	 * Method to get iterator pointing to the end of the list
	 */
	Iterator end() const
    {
	    return Iterator(nullptr);
    }

	/**
	 * \brief Метод обміну вмісту двох списків місцями
	 * (Method to swap contents of two lists)
	 * \param other - інший список
	 */
	void swap(LinkedList& other) noexcept
	{
        std::swap(head, other.head);
        std::swap(listSize, other.listSize);
    }
    /**
	 * \brief Шаблон функції для розділення списку на основі предиката
	 * (Function template to split the list based on a predicate)
	 * \tparam T - тип даних, що зберігається у списку. 
	 * \tparam Predicate - тип предикату
	 * \param list - список, до якого буде застосований предикат
	 * \param pred - предикат
	 */
    template<typename Predicate>
    LinkedList<T> split_when(Predicate pred) {
        LinkedList<T> newList;
        Node* current = head.get();
        while (current && !pred(current->data)) {
            newList.push_front(std::move(current->data));
            pop_front();
            current = head.get();
        }
        return newList;
    }
};