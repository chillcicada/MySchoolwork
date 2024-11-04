from ultralytics import YOLO

model = YOLO('trained/best.pt')

metrics = model.val()

print(metrics.box.map)
