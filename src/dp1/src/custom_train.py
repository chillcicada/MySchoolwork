import albumentations as A
import numpy as np
import torch
from datasets import LoadImagesAndLabels

augmentation_pipeline = A.Compose(
    [A.RandomContrast(limit=(0.2, 0.5), p=0.8)],
    bbox_params=A.BboxParams(format='yolo'),
)


class CustomDataset(LoadImagesAndLabels):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

    def __getitem__(self, index):
        img, labels, paths, shapes = super().__getitem__(index)

        img_np = img.permute(1, 2, 0).numpy()  # CHW -> HWC
        img_np = (img_np * 255).astype('uint8')

        augmented = augmentation_pipeline(
            image=img_np, bboxes=labels[:, 1:].tolist(), class_labels=labels[:, 0].tolist()
        )

        img_aug = augmented['image']
        img_aug = img_aug.astype(np.float32) / 255.0
        img_aug = torch.from_numpy(img_aug).permute(2, 0, 1)  # HWC -> CHW

        if len(augmented['bboxes']) > 0:
            labels = torch.tensor(
                np.column_stack([augmented['class_labels'], augmented['bboxes']]), dtype=torch.float32
            )

        return img_aug, labels, paths, shapes


train_dataset = CustomDataset(path='your_dataset.yaml')
