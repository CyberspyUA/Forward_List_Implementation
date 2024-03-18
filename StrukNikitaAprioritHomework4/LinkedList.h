#pragma once
#include <initializer_list>
#include <functional>
#include <memory>

template <typename T>
class LinkedList
{
private:
	/**
	 * \brief ��������� Node ��� ��������� ����� �� ���������� ���������
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
	 * \brief �������� Head �� ������ �������� �� ����� size ��� ��������� ������ ������.
	 * (The Head pointer to the first indicator and the size variable to store the size of the list)
	 */
	std::unique_ptr<Node> head;
	size_t listSize;
public:
	/**
	 *
	 * \brief ����������� �� �������������
	 * (Default Constructor)
	 */
	LinkedList() : head(nullptr), listSize(0)
	{
	}

	/** ����������� ������ ������������
	 * \brief
	 * (Initializer List Constructor)
	 * \param initializerList - ������ ������������ (an initializer list).
	 */
	LinkedList(const std::initializer_list<T>& initializerList) : LinkedList()
	{
		for(const auto& item: initializerList)
		{
			push_front(item);
		}
	}

	/**
	 * \brief ����������� ���������.
	 * (Copy Constructor)
	 * \param other - ����� ������ (another list).
	 */
	LinkedList(const LinkedList& other) : LinkedList()
	{
        for (auto it = other.begin(); it != other.end(); ++it)
            push_front(*it);
    }

	/**
	 * \brief ����������� ����������
	 * (Move Constructor)
	 * \param other - ����� ������ (another list).
	 */
	LinkedList(LinkedList&& other) noexcept : head(std::move(other.head)), listSize(other.listSize)
	{
        other.listSize = 0;
    }

	/**
	 * \brief �������� ��������� ��ﳿ
	 * (Copy Assignment Operator)
	 * \param other - ����� ������ (another list).
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
	 * \brief �������� ��������� ����������
	 * (Move Assignment Operator)
	 * \param other - ����� ������ (another list).
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
	 * \brief ����� ������� �������� �� ������� ������
	 * (Method to insert item at the beginning of the list)
	 * \param value - �������, ���� ���� ������ �� ������
	 */
	void push_front(const T& value)
	{
        std::unique_ptr<Node> newNode = std::make_unique<Node>(value);
        newNode->nextNode = std::move(head);
        head = std::move(newNode);
        ++listSize;
    }

	/**
	 * \brief ����� ��������� ������ ������ 
	 * (Method to get the size of the list)
	 */
	size_t getSize() const
	{
        return listSize;
    }

	/**
	 * \brief ����� ��������� ������� �������� � ������
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
	 * \brief ����� ��� ��������, �� ������ �������
	 * (Method to check if the list is empty) 
	 */
	bool empty() const
	{
        return listSize == 0;
    }
    /* ���� Iterator ��� �������� ��� ������� 
     * (Iterator class to iterate over the list).
     */
    class Iterator
	{
    private:
        Node* currentNode;
    public:
        Iterator(Node* node) : currentNode(node) {}

        /**
         * \brief �������� ������������ ��� ��������� ����� � currentNode
         *  (Dereference operator to get the data at current node)
         */
        T& operator*() const
		{
            return currentNode->data;
        }

        /**
         * \brief �������� ���������� ��� �������� �� ���������� �����
         * (Increment operator to move to the next node)
         */
        Iterator& operator++()
		{
            currentNode = currentNode->nextNode.get();
            return *this;
        }

        /**
         * \brief �������� �������� ��� ��������� ���������
         * (Inequality operator to compare iterators)
         * \param other - ����� ��������.
         */
        bool operator!=(const Iterator& other) const
		{
            return currentNode != other.currentNode;
        }
    };

	/**
	 * \brief ����� ��������� ���������, �� ����� �� ������� ������
	 *  Method to get iterator pointing to the beginning of the list
	 */
	Iterator begin() const
    {
	    return Iterator(head.get());
    }

	/**
	 * \brief ����� ��������� ���������, �� ����� �� ����� ������
	 * Method to get iterator pointing to the end of the list
	 */
	Iterator end() const
    {
	    return Iterator(nullptr);
    }

	/**
	 * \brief ����� ����� ����� ���� ������ ������
	 * (Method to swap contents of two lists)
	 * \param other - ����� ������
	 */
	void swap(LinkedList& other) noexcept
	{
        std::swap(head, other.head);
        std::swap(listSize, other.listSize);
    }
    /**
	 * \brief ������ ������� ��� ��������� ������ �� ����� ���������
	 * (Function template to split the list based on a predicate)
	 * \tparam T - ��� �����, �� ���������� � ������. 
	 * \tparam Predicate - ��� ���������
	 * \param list - ������, �� ����� ���� ������������ ��������
	 * \param pred - ��������
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