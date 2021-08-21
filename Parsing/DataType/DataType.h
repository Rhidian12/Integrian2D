#pragma once

#include <stdint.h>
#include <type_traits>
#include <memory>

namespace Integrian2D
{
	constexpr size_t Hash(size_t x) // https://stackoverflow.com/questions/664014/what-integer-hash-function-are-good-that-accepts-an-integer-hash-key
	{
		x = ((x >> 16) ^ x) * 0x45d9f3b;
		x = ((x >> 16) ^ x) * 0x45d9f3b;
		x = (x >> 16) ^ x;
		return x;
	}

	template<typename Fundamental, int Line>
	static constexpr size_t hash_v{ Hash(Hash(__COUNTER__) ^ Hash(Line)) };

	//enum class DataType : size_t
	//{
	//	uint8_t = hash_v<uint8_t, __LINE__>,
	//	uint16_t = hash_v<uint16_t, __LINE__>,
	//	uint32_t = hash_v<uint32_t, __LINE__>,
	//	uint64_t = hash_v<uint64_t, __LINE__>,
	//	int8_t = hash_v<int8_t, __LINE__>,
	//	int16_t = hash_v<int16_t, __LINE__>,
	//	int32_t = hash_v<int32_t, __LINE__>,
	//	int64_t = hash_v<int64_t, __LINE__>,
	//	floatP = hash_v<float, __LINE__>,
	//	doubleP = hash_v<double, __LINE__>,
	//	string = hash_v<std::string, __LINE__>
	//};

	enum class DataType : size_t
	{
		uint8_t = 0,
		uint16_t = 1,
		uint32_t = 2,
		uint64_t = 3,
		int8_t = 4,
		int16_t = 5,
		int32_t = 6,
		int64_t = 7,
		floatP = 8,
		doubleP = 9,
		string = 10
	};

	class IReadData
	{
	public:
		virtual ~IReadData() = default;
	};

	template<typename Data>
	class ReadDataImpl final : public IReadData
	{
	public:
		ReadDataImpl(Data data)
			: m_Data{ data }
		{}

		Data GetData() const noexcept
		{
			return m_Data;
		}

	private:
		Data m_Data;
	};

	class ReadData final
	{
	public:
		ReadData()
			: m_pData{}
			, m_DataType{}
		{}

		template<typename Data>
		ReadData(Data data, DataType dataType)
			: m_pData{ new ReadDataImpl{ data } }
			, m_DataType{ dataType }
		{}

		DataType GetDataType() const noexcept
		{
			return m_DataType;
		}

		template<typename Data>
		Data GetData() const noexcept
		{
			return static_cast<ReadDataImpl<Data>*>(m_pData.get())->GetData();
		}

	private:
		std::shared_ptr<IReadData> m_pData;
		DataType m_DataType;
	};
}