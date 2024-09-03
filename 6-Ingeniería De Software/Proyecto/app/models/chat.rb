class Chat < ApplicationRecord
  belongs_to :actividad
  belongs_to :user1, class_name: 'User'
  belongs_to :user2, class_name: 'User' #actividads creator
  has_many :messages, dependent: :destroy

  def self.between_users(user1, user2)
    where(user1_id: user1, user2_id: user2)
      .or(where(user1_id: user2, user2_id: user1))
  end
end
