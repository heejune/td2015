//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
//*********************************************************

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Windows;
using System.Windows.Input;
using System.Windows.Media.Imaging;

namespace PhotoFilter.WPF
{
    public class ImageItem : INotifyPropertyChanged
    {
        public string Name { get; set; }
        private BitmapImage _image = null;
        public BitmapImage Image { 
            get {
                if (_image == null)
                {
                    _image = new BitmapImage();

                    _image.BeginInit();
                    _image.UriSource = Uri;
                    _image.DecodePixelWidth = 150;
                    _image.EndInit();
                    OnPropertyChanged();
                }
                return _image;
            }
            set { _image = value; }
        }
        public Uri Uri { get; set; }

        public event PropertyChangedEventHandler PropertyChanged;

        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
            }
        }
    }
    public class MainPageViewModel
    {
        public List<ImageItem> Images { get; set; }
        public MainPageViewModel()
        {
            Images = new List<ImageItem>();

            var files = GetAllFiles();
            var pictures = RemoveInvalidFileTypes(files);
            LoadPictures(pictures);
        }

        private void LoadPictures(string[] pictures)
        {
            Images.Clear();

            foreach (var picture in pictures)
            {
                if (Utilities.IsValidImageFile(picture))
                {
                    ImageItem image = new ImageItem();
                    image.Uri = new Uri(picture);
                    image.Name = picture.Substring(picture.LastIndexOf(@"\") + 1);
                    Images.Add(image);
                }
            }
        }

        private string[] RemoveInvalidFileTypes(string[] files)
        {
            var validFiles = new List<string>();

            foreach (var file in files)
            {
                if (Utilities.IsValidImageFile(file))
                {
                    validFiles.Add(file);
                }
            }

            return validFiles.ToArray();
        }

        private string[] GetAllFiles()
        {
            return Utilities.GetListOfFiles(Utilities.PhotoPath);
        }

    }

    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        MainPageViewModel _viewModel;
        public MainWindow()
        {
            InitializeComponent();
        }

        protected override void OnActivated(EventArgs e)
        {
            if (_viewModel == null)
            { 
                _viewModel = new MainPageViewModel();
                this.DataContext = _viewModel;
                base.OnActivated(e);
            }
        }

        private void MainListView_MouseDoubleClick(object sender, MouseButtonEventArgs e)
        {
            ImagePage imagePage = new ImagePage(MainListView);
            imagePage.Show();
        }

        bool _processing = false;
        private void ProcessingButton_Click(object sender, RoutedEventArgs e)
        {
            if (_processing)
            {
                _processing = false;
                ProcessingStatus.Visibility = Visibility.Collapsed;
                ProcessingButton.Content = "Start Background Processing";
            }
            else
            {
                _processing = true;
                ProcessingStatus.Visibility = Visibility.Visible;
                ProcessingButton.Content = "Stop Background Processing";
                DoBackgroundImageProcessing();
            }
        }

        private void DoBackgroundImageProcessing()
        {
            //Task.Run(() =>
            //{
            //    while (_processing)
            //    {
            //        for (int i = 0; i < 1000000; i++)
            //        {
            //        }
            //        Thread.Sleep(10);
            //    }
            //});
        }
    }
}
