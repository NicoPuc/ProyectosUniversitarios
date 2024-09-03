class Review < ApplicationRecord
  belongs_to :user
  belongs_to :actividad
  validate :unique_review_by_user_per_actividad
  validates :content, presence: true
  validates :rating, presence: true, inclusion: { in: 1..5 }
  def unique_review_by_user_per_actividad
    existing_review = Review.find_by(user_id: user_id, actividad_id: actividad_id)
    if existing_review && existing_review != self
      errors.add(:base, "Ya tienes una reseña asociada a esta actividad")
    end
  end
end
