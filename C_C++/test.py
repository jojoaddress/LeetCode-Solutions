
    def create_dataset(data_root, dataset_name, train, transform=None, memory=False, label_file=None,
                       ):
        has_subfolder = False
        if dataset_name in ['cifar10', 'cifar20', 'cifar100','tiny_imagenet']:
            
            
            dataset_type = {'cifar10': torchvision.datasets.CIFAR10,
                            'cifar20': torchvision.datasets.CIFAR100,
                            'cifar100': torchvision.datasets.CIFAR100}[dataset_name]
            class_names = {'cifar10': ['plane', 'car', 'bird', 'cat', 'deer', 'dog', 'frog', 'horse', 'ship', 'truck'],
                            'cifar20': ['aquatic mammals', 'fish', 'flowers', 'food containers', 'fruit and vegetables',
                                        'household electrical devices', 'househould furniture', 'insects', 'large carnivores',
                                        'large man-made outdoor things', 'large natural outdoor scenes', 'large omnivores and herbivores',
                                        'medium-sized mammals', 'non-insect invertebrates', 'people', 'reptiles', 'small mammals', 'trees',
                                        'vehicles 1', 'vehicles 2'],
                            'cifar100': torchvision.datasets.CIFAR100}[dataset_name]
            has_subfolder = True
            dataset = dataset_type(root=data_root, train=train, transform=transform, download=True)
            #dataset = dataset_type(data_root, train, transform)
            if dataset_name == 'cifar20':
                targets = np.array(dataset.targets)
                super_classes = [
                    [72, 4, 95, 30, 55],
                    [73, 32, 67, 91, 1],
                    [92, 70, 82, 54, 62],
                    [16, 61, 9, 10, 28],
                    [51, 0, 53, 57, 83],
                    [40, 39, 22, 87, 86],
                    [20, 25, 94, 84, 5],
                    [14, 24, 6, 7, 18],
                    [43, 97, 42, 3, 88],
                    [37, 17, 76, 12, 68],
                    [49, 33, 71, 23, 60],
                    [15, 21, 19, 31, 38],
                    [75, 63, 66, 64, 34],
                    [77, 26, 45, 99, 79],
                    [11, 2, 35, 46, 98],
                    [29, 93, 27, 78, 44],
                    [65, 50, 74, 36, 80],
                    [56, 52, 47, 59, 96],
                    [8, 58, 90, 13, 48],
                    [81, 69, 41, 89, 85],
                ]
                import copy
                copy_targets = copy.deepcopy(targets)
                for i in range(len(super_classes)):
                    for j in super_classes[i]:
                        targets[copy_targets == j] = i
                dataset.targets = targets.tolist()
        else:
            data_path = osp.join(data_root, dataset_name)
            dataset_type = torchvision.datasets.ImageFolder
            if 'train' in os.listdir(data_path):
                has_subfolder = True
                dataset = dataset_type(
                    osp.join(data_root, dataset_name, 'train' if train else 'val'), transform=transform)
            else:
                dataset = dataset_type(osp.join(data_root, dataset_name), transform=transform)
                
        if label_file is not None:
            new_labels = np.load(label_file).flatten()
            assert len(dataset.targets) == len(new_labels)
            noise_ratio = (1 - np.mean(np.array(dataset.targets) == new_labels))
            dataset.targets = new_labels.tolist()
            print(f'load label file from {label_file}, possible noise ratio {noise_ratio}')
        return dataset, has_subfolder, class_names