class Request < ApplicationRecord
  belongs_to :user
  belongs_to :actividad
  


  validates :status, presence: true, inclusion: { in: ["pending", "accepted", "rejected"] }
  validates :description, :fecha, presence: true
  validates :user_id, uniqueness: { scope: :actividad_id, message: "ya ha solicitado unirse a esta actividad" }

end