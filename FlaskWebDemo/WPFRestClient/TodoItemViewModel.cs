using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Net.Http;
using System.Net.Http.Headers;
using System.Text;
using System.Threading.Tasks;
using System.Web.Script.Serialization;
using System.Windows;
using System.Windows.Input;

namespace WPFRestClient
{
    class TodoItemViewModel : INotifyPropertyChanged
    {
        private List<TodoItem> todoItems;

        public TodoItemViewModel()
        {
        }

        public async Task Refresh()
        {
            // Sample reference:
            // http://blogs.msdn.com/b/aonishi/archive/2014/12/16/wpfrest.aspx
            // https://code.msdn.microsoft.com/windowsdesktop/How-to-use-MVVM-Pattern-0e2f4571

            var httpClient = new HttpClient();

            httpClient.BaseAddress = new Uri("http://localhost:5555/");

            try
            {
                HttpResponseMessage response = await httpClient.GetAsync("/todo/api/v1.0/tasks");

                if (response.IsSuccessStatusCode)
                {
                    response.EnsureSuccessStatusCode();

                    string jsonString = await response.Content.ReadAsStringAsync();

                    // extract arrays from 'tasks: []'
                    var JsonResult = (new JavaScriptSerializer()).Deserialize<TodoItemResponse>(jsonString);
                    // converts List to ObservableCollection
                    ObservableCollection<TodoItem> oc = new ObservableCollection<TodoItem>(JsonResult.tasks);

                    TodoItems = oc;
                }
                else
                {
                    MessageBox.Show("Error Code" + response.StatusCode + " : Message - " + response.ReasonPhrase);
                }
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message);
                throw;
            }
        }

        public async Task Remove(int id)
        {
            var httpClient = new HttpClient();
            var uri = new Uri("http://localhost:5555/todo/api/v1.0/tasks/" + id);

            try
            {
                var response = await httpClient.DeleteAsync(uri);

                if (response.IsSuccessStatusCode)
                {
                    var result = await response.Content.ReadAsStringAsync();
                    var succeeded = (new JavaScriptSerializer()).Deserialize<bool>(result);
                }
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message);
                throw;
            }
        }

        public async Task Add(TodoItem item)
        {
            var httpClient = new HttpClient();
            var uri = new Uri("http://localhost:5555/todo/api/v1.0/tasks");

            string jsonToPost = new JavaScriptSerializer().Serialize(new
            {
                title = item.Title,
                description = item.Description,
                imasge = item.Image
            });

            //httpClient.DefaultRequestHeaders.Accept.Add(new MediaTypeWithQualityHeaderValue("application/json"));

            try
            {
                HttpResponseMessage response = await httpClient.PostAsync(uri,
                   new StringContent(jsonToPost, Encoding.UTF8, "application/json"));

                if (response.IsSuccessStatusCode)
                {
                    var result = await response.Content.ReadAsStringAsync();
                }
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message);
                throw;
            }
        }

        public async Task Update(TodoItem item)
        {
            var httpClient = new HttpClient();
            var uri = new Uri("http://localhost:5555/todo/api/v1.0/tasks/" + item.Id);

            //Dictionary<string, string> jsonObj = new Dictionary<string, string>();
            //jsonObj.Add("title", item.Title);
            //jsonObj.Add("description", item.Description);
            //jsonObj.Add("image", item.Image);
            //jsonObj.Add("done", item.Done.ToString());

            //JavaScriptSerializer serializer = new JavaScriptSerializer();
            //var jsonContent = new StringContent(serializer.Serialize(jsonObj), Encoding.UTF8);
            //jsonContent.Headers.ContentType = new MediaTypeWithQualityHeaderValue("application/json");
            //httpClient.DefaultRequestHeaders.Accept.Add(new MediaTypeWithQualityHeaderValue("application/json"));

            string jsonToPut = new JavaScriptSerializer().Serialize(new
            {
                title = item.Title,
                description = item.Description,
                image = item.Image,
                done = item.Done
            });

            try
            {
                HttpResponseMessage response = await httpClient.PutAsync(uri,
                        new StringContent(jsonToPut, Encoding.UTF8, "application/json"));

                if (response.IsSuccessStatusCode)
                {
                    var result = await response.Content.ReadAsStringAsync();
                }
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message);
                throw;
            }
        }

        #region ObservableCollection Property
        public ObservableCollection<TodoItem> TodoItems
        {
            get
            {
                if (todoItems == null)
                    return new ObservableCollection<TodoItem>();

                ObservableCollection<TodoItem> oc = new ObservableCollection<TodoItem>(todoItems);
                return oc;
            }

            set
            {
                todoItems = value.ToList();
                NotifyPropertyChanged("TodoItems");
            }
        }

        protected void NotifyPropertyChanged(String info)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(info));
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;
        #endregion

        #region ICommand Implementation
        private ICommand _updaterCommandInstance;

        public ICommand UpdateCommand
        {
            get
            {
                if (_updaterCommandInstance == null)
                    _updaterCommandInstance = new Updater(this);
                return _updaterCommandInstance;
            }
            set
            {
                _updaterCommandInstance = value;
            }
        }
        private class Updater : ICommand
        {
            private TodoItemViewModel _viewModel;
            public Updater(TodoItemViewModel _vm)
            {
                _viewModel = _vm;
            }

            #region ICommand Members
            public bool CanExecute(object parameter)
            {
                return true;
            }
            public event EventHandler CanExecuteChanged;

            public async void Execute(object parameter)
            {
                if (parameter != null)
                {
                    var item = parameter as TodoItem;
                    await _viewModel.Update(item);
                }
            }
            #endregion
        } 
        #endregion
    }
}
