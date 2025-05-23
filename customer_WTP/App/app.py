from flask import Flask, render_template, request, jsonify
import joblib
import numpy as np
import os

app = Flask(__name__)

# Load the trained model
model_path = 'models/final_rf_model.pkl'
if os.path.exists(model_path):
    model = joblib.load(model_path)
else:
    model = None

@app.route('/')
def home():
    return render_template('index.html')

@app.route('/predict', methods=['POST'])
def predict():
    if model is None:
        return render_template('error.html', 
                             message="Model not found. Please ensure final_rf_model.pkl exists.")
    
    try:
        # Extract features from form
        features = [
            float(request.form.get('baseFare', 0)),
            float(request.form.get('totalFare', 0)),
            int(request.form.get('seatsRemaining', 0)),
            float(request.form.get('totalTravelDistance', 0)),
            int(request.form.get('isBasicEconomy', 0)),
            int(request.form.get('isRefundable', 0)),
            int(request.form.get('isNonStop', 0)),
            int(request.form.get('booking_window', 0)),
            int(request.form.get('search_month', 1)),
            int(request.form.get('flight_month', 1)),
            int(request.form.get('search_weekday', 0)),
            int(request.form.get('flight_weekday', 0)),
            int(request.form.get('search_weekend', 0)),
            int(request.form.get('flight_weekend', 0)),
            int(request.form.get('is_weekend', 0)),
            int(request.form.get('is_holiday_search', 0)),
            int(request.form.get('is_holiday_flight', 0)),
            int(request.form.get('search_season', 0)),
            int(request.form.get('flight_season', 0)),
            float(request.form.get('price_discount', 0))
        ]
        
        # Make prediction
        features_array = np.array([features])
        prediction = model.predict(features_array)[0]
        
        return render_template('result.html', prediction=prediction)
        
    except Exception as e:
        return render_template('error.html', message=f"Error occurred during prediction: {str(e)}")

@app.route('/api/predict', methods=['POST'])
def api_predict():
    """API endpoint for JSON requests"""
    if model is None:
        return jsonify({'error': 'Model not found'})
    
    try:
        data = request.get_json()
        features = [
            float(data.get('baseFare', 0)),
            float(data.get('totalFare', 0)),
            int(data.get('seatsRemaining', 0)),
            float(data.get('totalTravelDistance', 0)),
            int(data.get('isBasicEconomy', 0)),
            int(data.get('isRefundable', 0)),
            int(data.get('isNonStop', 0)),
            int(data.get('booking_window', 0)),
            int(data.get('search_month', 1)),
            int(data.get('flight_month', 1)),
            int(data.get('search_weekday', 0)),
            int(data.get('flight_weekday', 0)),
            int(data.get('search_weekend', 0)),
            int(data.get('flight_weekend', 0)),
            int(data.get('is_weekend', 0)),
            int(data.get('is_holiday_search', 0)),
            int(data.get('is_holiday_flight', 0)),
            int(data.get('search_season', 0)),
            int(data.get('flight_season', 0)),
            float(data.get('price_discount', 0))
        ]
        
        features_array = np.array([features])
        prediction = model.predict(features_array)[0]
        
        return jsonify({
            'prediction': round(prediction, 4),
            'interpretation': f'Customer willingness to pay ratio: {round(prediction, 4)}'
        })
        
    except Exception as e:
        return jsonify({'error': str(e)})

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=5000)
