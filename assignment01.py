# 컴퓨터비전 과제1 디지털미디어학과 201921782 박종원
import cv2
import numpy as np

cnt = 0
# 동전 검출 함수, 파라미터로 이미지 경로, 이미지 번호
def hough_circles(input_image, cnt):
    # input image -> gray
    gray = cv2.cvtColor(input_image, cv2.COLOR_BGR2GRAY)
    gray = cv2.convertScaleAbs(gray, alpha=1.3, beta=-50)
    # 가우시안 블러 적용 -> 이미지 노이즈 값 최소화
    blurred = cv2.GaussianBlur(gray, (9, 9), 3) 
    # HoughCircles을 사용하여 동전 detect
    circles = cv2.HoughCircles(blurred, cv2.HOUGH_GRADIENT, dp=1.3, minDist=40, param1=120, param2=50, minRadius=35, maxRadius=130)
    
    if circles is not None:
        circles = np.uint16(np.around(circles))
        for i in circles[0, :]:
            center = (i[0], i[1])
            radius = i[2]

            cv2.circle(input_image, center, 3, (0, 255, 0), -1, 8, 0)
            cv2.circle(input_image, center, radius, (0, 0, 255), 3, 8, 0)
    
    print(f"coin{cnt} 의 개수: {len(circles[0]) if circles is not None else 0}")
    
    return input_image

# 동전 번호에 따른 결과값 출력, 키보드 "q" 혹은 탭 클릭 시 다음 동전 이미지로 이동
for i in range(0, 6):
    input_image = cv2.imread(f'/Users/parkjongwon/Desktop/coins{i}.jpg')
    result_image = hough_circles(input_image, cnt)
    cv2.imshow(f'coin{i}', result_image)
    cv2.waitKey() == ord('q')
    cv2.destroyAllWindows()
    cnt += 1