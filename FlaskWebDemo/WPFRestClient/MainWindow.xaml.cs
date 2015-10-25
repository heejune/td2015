using System;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace WPFRestClient
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        TodoItemViewModel viewModel = new TodoItemViewModel();

        public MainWindow()
        {
            InitializeComponent();
        }

        private async void btnRefresh_Click(object sender, RoutedEventArgs e)
        {
            await viewModel.Refresh();
            DataContext = viewModel;
        }

        private async void btnRemove_Click(object sender, RoutedEventArgs e)
        {
            var item = TodoItemList.SelectedItem as TodoItem;
            await viewModel.Remove(item.Id);
        }

        private async void btnAdd_Click(object sender, RoutedEventArgs e)
        {
            TodoItem item = new TodoItem();
            var count = viewModel.TodoItems.Count();
            item.Id = count;
            item.Title = "Add new todo item";
            item.Image = "/image/invalid.jpg";
            item.Description = "This will be added";
            item.Done = false;

            await viewModel.Add(item);
        }
    }
}
