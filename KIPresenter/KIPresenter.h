#pragma once

using System::ComponentModel::INotifyPropertyChanged;
using System::ComponentModel::PropertyChangedEventArgs;
using System::ComponentModel::PropertyChangedEventHandler;
namespace KIPresenter {
	public ref class SphereViewModel : public INotifyPropertyChanged
	{
	public:
		virtual event PropertyChangedEventHandler ^PropertyChanged;
		// TODO: このクラスのメソッドをここに追加します。
		SphereViewModel()
		{}
	};

	// データモデル
	class DataModel {
	public:

		DataModel()
			: _value(3.0) {
		}

		double GetValue() const {
			return _value;
		}

		bool SetValue(double value) {
			if (_value == value) {
				return false;
			}
			_value = value;
			return true;
		}

	private:
		double _value;
	};

	// ビューモデル
	public ref class ViewModel : public INotifyPropertyChanged {
	public:

		virtual event PropertyChangedEventHandler ^PropertyChanged;

		property double Value {

			double get() {
				return _dataModel->GetValue();
			}

			void set(double value) {
				if (_dataModel->SetValue(value)) {
					Cube cube;
					CubeArgs args;
					args.min = vec3(0);
					args.max = vec3(1);
					cube.Build(args);
					PropertyChanged(this, gcnew PropertyChangedEventArgs("Value"));
				}
			}

		}

		ViewModel()
			: _dataModel(new DataModel())
		{
		}

		~ViewModel() {
			this->!ViewModel();
		}

		!ViewModel() {
			delete _dataModel;
		}

	private:
		DataModel *_dataModel;
	};
}
